#!/usr/bin/env python

from gi.repository import Gtk,Gdk
import cairo
from array import array
import math, time, os, struct

class Image:
	def __init__(self,w,h,data,label):
		self.w = w
		self.h = h
		self.data = data
		self.label = label

	def draw(self,ctx,w,h):
		scale = w/self.w

		for j in range(self.h):
			for i in range(self.w):
				w = self.data[j*28+i]/255.0
				ctx.set_source_rgb (w, w, w)
				ctx.rectangle( i*scale, j*scale, scale, scale)
				ctx.fill()

class Point:
	def __init__(self,x,y):
		self.x = x
		self.y = y

	def distance(self,x,y):
		return (self.x - x)**2 + (self.y - y)**2

	def draw(self,ctx,active):
		if active:	
			ctx.set_source_rgb (1, 0, 0)
			ctx.arc(self.x, self.y, 10, 0, math.pi*2)
		else:	
			ctx.set_source_rgb (1, 0, 0) # Solid color
			ctx.arc(self.x, self.y, 5, 0, math.pi*2)

		ctx.fill()

	def angleTo(self,other):
		dx = other.x - self.x
		dy = other.y - self.y

		angle = math.atan2(dy,dx)

		if angle < 0:
			angle += math.pi*2

		return angle

class Segment:
	def __init__(self,a,b):
		self.a = a
		self.b = b

	def draw(self,ctx,active):
		ctx.set_source_rgb(0, 1, 0)
		ctx.set_line_width(2)

		ctx.move_to(self.a.x, self.a.y)
		ctx.line_to(self.b.x, self.b.y)
		ctx.stroke()

class Angle:
	def __init__(self,p,a,b,s,e):
		self.point = p
		self.a = a
		self.b = b
		self.start = s
		self.end = e

	def draw(self,ctx):
		ctx.set_source_rgb (0, 0, 1)
		ctx.move_to(self.point.x, self.point.y)
		ctx.arc(self.point.x, self.point.y, 15, self.start, self.end)
		ctx.line_to(self.point.x, self.point.y)

		ctx.fill()

def readMNIST(images_path = "data/train-images", lables_path  = "data/train-labels"):
	with open( lables_path, 'rb') as file:
		magic, size = struct.unpack(">II", file.read(8))
		if magic != 2049:
			raise ValueError('Magic number mismatch, expected 2049,'
							 'got {}'.format(magic))

		labels = array("B", file.read())

	with open(images_path, 'rb') as file:
		magic, size, rows, cols = struct.unpack(">IIII", file.read(16))
		if magic != 2051:
			raise ValueError('Magic number mismatch, expected 2051,'
							 'got {}'.format(magic))

		image_data = array("B", file.read())

	images = []
	for i in range(size):
		images.append(Image(28,28,image_data[i*28*28:(i+1)*28*28],labels[i]))

	return images

def angleDistance(a,b):
	res = b - a
	if res < 0:
		res += math.pi*2

	return res

class Window(Gtk.Window):

	def __init__(self,title = "Window",width = 560,height = 560):
		super(Window, self).__init__()

		self.w = width
		self.h = height

		self.table = Gtk.Table(2, 6, False)
		self.add(self.table)

		self.darea = Gtk.DrawingArea()
		self.darea.set_size_request(width, height)
		self.darea.connect("draw", self.on_draw)
		self.darea.set_events(Gdk.EventMask.BUTTON_PRESS_MASK | Gdk.EventMask.POINTER_MOTION_MASK | Gdk.EventMask.KEY_PRESS_MASK )
		self.darea.connect("button-press-event", self.on_button_press)
		self.darea.connect("motion-notify-event", self.on_mouse_move)
		self.connect("key-press-event", self.on_key)


		self.currentImageIndex = 0
		self.images = readMNIST()
		self.points = []
		self.segments = []
		self.angles = []

		self.hoverPoint = None
		self.lineStart = None
		self.lineEnd = None

		next = Gtk.Button("Next Image")
		next.connect("clicked", self.loadNextImage)

		previous = Gtk.Button("Previous Image")
		previous.connect("clicked", self.loadPreviousImage)

		save = Gtk.Button("Save")
		save.connect("clicked", self.save)

		self.table.attach(save, 0, 1, 0, 1)
		self.table.attach(previous, 4, 5, 0, 1)
		self.table.attach(next, 5, 6, 0, 1)

		self.table.attach(self.darea,0,6,1,2)

		self.set_title(title)

		self.set_position(Gtk.WindowPosition.CENTER)
		self.connect("delete-event", Gtk.main_quit)
		self.show_all()


	def on_draw(self, widget, ctx):

		self.images[self.currentImageIndex].draw(ctx,self.w,self.h)

		if self.lineStart != None:
			ctx.set_source_rgb(0, 1, 0)
			ctx.set_line_width(2)

			ctx.move_to(self.lineStart.x, self.lineStart.y)
			ctx.line_to(self.lineEnd[0], self.lineEnd[1]) 
			ctx.stroke()

		for a in self.angles:
			a.draw(ctx)

		for s in self.segments:
			s.draw(ctx,False)

		for p in self.points:
			p.draw(ctx,p == self.hoverPoint or p == self.lineStart)

	def save(self,ev):
		dialog = Gtk.FileChooserDialog("Save Project", self,Gtk.FileChooserAction.SAVE, (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL ,Gtk.STOCK_OK, Gtk.ResponseType.OK))
		dialog.set_filename("tre.mod")

		filter = Gtk.FileFilter()
		filter.set_name("Models")
		filter.add_pattern("*.mod")

		dialog.add_filter(filter)


		response = dialog.run()
		if response == Gtk.ResponseType.OK:
			path = dialog.get_filename()
			print(path, 'selected')
			f = open(path,'w')
			f.write('label: '+str(self.images[self.currentImageIndex].label)+"\n")
			f.write('points:\n')
			for p in self.points:
				f.write(str(p.x*2/self.w - 1)+" "+str(p.y*2/self.h - 1)+"\n")
			f.write('segments:\n')
			for s in self.segments:
				f.write(str(self.points.index(s.a))+" "+str(self.points.index(s.b))+"\n")		
			f.write('angles:\n')
			for s in self.angles:
				f.write(str(self.points.index(s.a))+" "+str(self.points.index(s.point))+" "+str(self.points.index(s.b))+"\n")	
			f.close() # you can omit in most cases as the destructor will call 

		elif response == Gtk.ResponseType.CANCEL:
			print 'Closed, no files selected'
		dialog.destroy()

	def on_key(self,w,ev):
		key = ev.keyval

		if key >= 48 and key <= 57:
			self.showNumber(key-48)
		else:
			if key == 65363:
				self.loadNextImage(None)
			if key == 65361:
				self.loadPreviousImage(None)



	def on_mouse_move(self,w,e):
		needRedraw = False

		if self.hoverPoint:
			self.hoverPoint = None
			needRedraw = True

		for p in self.points:
			if p.distance(e.x,e.y) < 100:
				self.hoverPoint = p
				needRedraw = True
				break

		if self.lineStart != None:
			needRedraw = True
			self.lineEnd = (e.x,e.y) 

		if needRedraw:
			self.darea.queue_draw()

	def reset(self):
		self.segments = []
		self.points = []
		self.angles = []
		self.darea.queue_draw()
	
	def showNumber(self,n):
		while True:
			self.currentImageIndex += 1
			if self.images[self.currentImageIndex].label == n:
				break
		self.reset()

	def loadNextImage(self,ev):
		self.currentImageIndex += 1
		self.reset()

	def loadPreviousImage(self,ev):
		self.currentImageIndex -= 1
		self.reset()

	def getConnectedPoints(self,point):
		res = []
		for s in self.segments:
			if s.a == point:
				res.append( (s.b,point.angleTo(s.b)) )
			elif s.b == point:
				res.append( (s.a,point.angleTo(s.a)) )

		return res

	def computeAngles(self):
		self.angles = []

		for point in self.points:
			connectedPoints = self.getConnectedPoints(point)
			if len(connectedPoints) < 2:
				continue

			sorted(connectedPoints, key = lambda x: x[1])

			count = len(connectedPoints) - 1

			for i in range(-1,len(connectedPoints)-1):
				#print(count)
				if count == 0:
					break
				if angleDistance(connectedPoints[i][1],connectedPoints[i+1][1]) < math.pi:
					count -= 1
					#print(connectedPoints[i][1]*180/(math.pi),connectedPoints[i+1][1]*180/(math.pi))
					self.angles.append(Angle(point,connectedPoints[i][0],connectedPoints[i+1][0],connectedPoints[i][1],connectedPoints[i+1][1]))


	def on_button_press(self, w, e):

		if e.button == 1:#left click
			if self.hoverPoint: #if clicked on point
				if self.lineStart != None and self.lineStart != self.hoverPoint:
					self.segments.append(Segment(self.lineStart,self.hoverPoint))
					self.computeAngles()
					self.lineStart = self.hoverPoint
				else:				
					self.lineStart = self.hoverPoint
					self.lineEnd = (e.x,e.y)
			else: #add point
				p = Point(e.x,e.y)
				self.hoverPoint = p
				p.active = True
				self.points.append(p)
		else:#right click
			if self.lineStart != None:#if drawing line
				self.lineStart = None #stop drawing
			elif self.hoverPoint != None: #else remove current point				
				self.points.remove(self.hoverPoint)
				self.segments = [s for s in self.segments if s.a != self.hoverPoint and s.b != self.hoverPoint]
				self.computeAngles()
				self.hoverPoint = None

		self.darea.queue_draw()

		
		
if __name__ == "__main__":  
	win = Window()
	Gtk.main()