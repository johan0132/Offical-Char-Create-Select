# Dentro de 
class Button(Window):
	....
	....
	
	# Despues de
	def SetAppendTextColor(self, idx, color) :
		....
		....
		
	# Agregar
	def AppendTextLine(self, text
		, font_size = localeInfo.UI_DEF_FONT
		, font_color = grp.GenerateColor(0.7607, 0.7607, 0.7607, 1.0)
		, text_sort = "center"
		, pos_x = None
		, pos_y = None) :
		textLine = TextLine()
		textLine.SetParent(self)
		textLine.SetFontName(font_size)
		textLine.SetPackedFontColor(font_color)
		textLine.SetText(text)
		textLine.Show()

		if not pos_x and not pos_y :
			textLine.SetPosition(self.GetWidth()/2, self.GetHeight()/2)
		else :
			textLine.SetPosition(pos_x, pos_y)

		textLine.SetVerticalAlignCenter()
		if "center" == text_sort :
			textLine.SetHorizontalAlignCenter()
		elif "right" == text_sort :
			textLine.SetHorizontalAlignRight()
		elif "left" == 	text_sort :
			textLine.SetHorizontalAlignLeft()
			
		self.TextChild.append(textLine)