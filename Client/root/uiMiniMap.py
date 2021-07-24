''' 1. '''
# Search
			self.serverInfo = self.GetChild("ServerInfo")

# Add below
			if app.ENABLE_RTT_STATISTICS:
				self.rttTextLine = self.GetChild("RTTTextLine")
				self.pktLossTextLine = self.GetChild("PacketLossTextLine")

''' 2. '''
# Search
	def OnUpdate(self):
		(x, y, z) = player.GetMainCharacterPosition()
		miniMap.Update(x, y)

		self.positionInfo.SetText("(%.0f, %.0f)" % (x / 100, y / 100))

# Add below
		if app.ENABLE_RTT_STATISTICS:
			if self.rttTextLine and self.pktLossTextLine:
				rtt = app.GetRTT()
				pktLossPct = app.GetPacketLossPct()

				if rtt > 300:
					self.rttTextLine.SetFontColor((255.00 / 255), (0.00 / 255), (0.00 / 255)) # r, g, b
				elif rtt > 100 and rtt < 300:
					self.rttTextLine.SetFontColor((255.00 / 255), (255.00 / 255), (0.00 / 255)) # r, g, b
				else:
					self.rttTextLine.SetFontColor((0.00 / 255), (255.00 / 255), (0.00 / 255)) # r, g, b

				self.rttTextLine.SetText("Ping: %s%dms" % ("+" if rtt > 999 else "", 999 if rtt > 999 else rtt))
				self.pktLossTextLine.SetText("(%.2f%% pkt loss)" % (pktLossPct))