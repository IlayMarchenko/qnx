--  Sample USB descriptors for a USB Audio device

-- complete templates for the .device, .fs_config, and .hs_config table values

USB_CONFIG_SELFPOWERED         = 0xC0
USB_CONFIG_REMOTEWAKEUP        = 0x20
USB_MAX_CURRENT                = 0

-- AC_HEADER + (total_clock_sources * clock_source_len) + (total_clock_selectors * clock_selector_len) + (total_input_terminals * input_terminal_len) + (total_output_terminals * output_terminal_size) + (total_class_audio_stream_general * class_audio_stream_general_length) + (total_class_audio_format_type1 * class_audio_format_type1_length)
SIZE_AUDIO_DESCS         = (0x9 + (1 * 0x8) + (1 * 0x8) + (2 * 0x11) + (2 * 0xc) + (2 * 0x10) + (2 * 0x06))

audio_control_descriptors = {
-- Audio Control Header Descriptor
	0x09,                   -- bLength
	0x24,                   -- bDescriptorType
	0x01,                   -- bDescriptorSubType
	0x00,                   -- bcdADC   (LSB)
	0x02,                   -- bcdADC   (MSB)
	0xFF,                   -- bCategory
	lsb(SIZE_AUDIO_DESCS),  -- wTotalLength (LSB)
	msb(SIZE_AUDIO_DESCS),  -- wTotalLength (MSB)
	0x00,                   -- bmControls

-- Audio Control Clock Source Descriptor
	0x08,                   -- bLength
	0x24,                   -- bDescriptorType
	0x0A,                   -- bDescriptorSubType
	0x01,                   -- bClockID
	0x01,                   -- bmAttribuets
	0x03,                   -- bmControls
	0x00,                   -- bmAssocTerminal
	0x00,                   -- iClockSource

-- Audio Control Clock Selector Descriptor
	0x08,                   -- bLength
	0x24,                   -- bDescriptorType
	0x0B,                   -- bDescripotrSubType
	0x02,                   -- bClockID
	0x01,                   -- bNrInPins
	0x01,                   -- bCSourceID(p)
	0x03,                   -- bmControls
	0x00,                   -- iClockSelector

-- Audio Control Input Terminal (Streaming) Function Descriptor
	0x11,                   -- bFunctionLength
	0x24,                   -- bDescriptorType
	0x02,                   -- bDescriptorSubType
	0x03,                   -- bTerminalID
	0x01,                   -- wTerminalType (LSB)
	0x01,                   -- wTerminalType (MSB)
	0x00,                   -- bAssocTerminal
	0x02,                   -- bCSourceID
	0x02,                   -- bNrChannels
	0x00,                   -- bmChannelConfig
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- iChannelNames
	0x00,                   -- bmControls
	0x00,                   -- Reserved
	0x00,                   -- iTerminal

-- Audio Control Output Terminal (Local playback device) Function Descriptor
	0x0c,                   -- bLength
	0x24,                   -- bDescriptorType
	0x03,                   -- bDescripotrSubType
	0x04,                   -- bTerminalID
	0x00,                   -- wTerminalType (LSB)
	0x03,                   -- wTerminalType (MSB)
	0x00,                   -- bAssocTerminal
	0x03,                   -- bSourceID
	0x02,                   -- bCSourceID
	0x00,                   -- bmControls
	0x00,                   -- Reserved
	0x00,                   -- iTerminal

-- Audio Control Input Terminal (Local capture device) Function Descriptor
	0x11,                   -- bLength
	0x24,                   -- bDescriptorType
	0x02,                   -- bDescripotrSubType
	0x05,                   -- bTerminalID
	0x00,                   -- wTerminalType (LSB)
	0x02,                   -- wTerminalType (MSB)
	0x00,                   -- bAssocTerminal
	0x02,                   -- bCSourceID
	0x02,                   -- bNrChannels
	0x00,                   -- bmChannelConfig
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- iChannelNames
	0x00,                   -- bmControls
	0x00,                   -- Reserved
	0x00,                   -- iTerminal

-- Audio Control Output Terminal (Streaming) Function Descriptor
	0x0c,                   -- bLength
	0x24,                   -- bDescriptorType
	0x03,                   -- bDescripotrSubType
	0x06,                   -- bTerminalID
	0x01,                   -- wTerminalType (LSB)
	0x01,                   -- wTerminalType (MSB)
	0x00,                   -- bAssocTerminal
	0x05,                   -- bSourceID
	0x02,                   -- bCSourceID
	0x00,                   -- bmControls
	0x00,                   -- Reserved
	0x00,                   -- iTerminal
}

audio_streaming_in_descriptors = {
-- Class Audio Stream General Function Descriptor
	0x10,                   -- bLength
	0x24,                   -- bDescriptorType
	0x01,                   -- bDescripotrSubType
	0x06,                   -- bTerminalLink
	0x00,                   -- bmControls
	0x01,                   -- bFormatType
	0x01,                   -- bFormats
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x02,                   -- bNrChannels
	0x00,                   -- bmChannelConfig
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- iChannelNames

-- Class Audio v2.0 Format Type1 Function Descriptor
	0x06,                   -- bLength
	0x24,                   -- bDescriptorType
	0x02,                   -- bDescripotrSubType
	0x01,                   -- bFormatType
	0x02,                   -- bSubFrameSize
	0x10,                   -- bBitResolution
}

audio_streaming_out_descriptors = {
-- Class Audio Stream General Function Descriptor
	0x10,                   -- bLength
	0x24,                   -- bDescriptorType
	0x01,                   -- bDescripotrSubType
	0x03,                   -- bTerminalLink
	0x00,                   -- bmControls
	0x01,                   -- bFormatType
	0x01,                   -- bFormats
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x02,                   -- bNrChannels
	0x00,                   -- bmChannelConfig
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- Reserved
	0x00,                   -- iChannelNames

-- Class Audio v2.0 Format Type1 Function Descriptor
	0x06,                   -- bLength
	0x24,                   -- bDescriptorType
	0x02,                   -- bDescripotrSubType
	0x01,                   -- bFormatType
	0x02,                   -- bSubFrameSize
	0x10,                   -- bBitResolution
}

audio = {}

audio.device = Device{
	bDeviceClass = 0x0,
	bDeviceSubClass = 0x0,
	bDeviceProtocol = 0x0,
	bMaxPacketSize = 64,
	idVendor = 0x1234,
	idProduct = 0xfff1,
	bcdDevice = 0x0200,
	manufacturer = 'QNX Software',
	product = 'USB Audio Accessory',
	serial = '123456789ABC',
	bNumConfigurations = 1,
}

audio.fs_config = Config{  -- full speed
	bConfigurationValue = 1,
	bmAttributes = USB_CONFIG_SELFPOWERED,
	bMaxPower = USB_MAX_CURRENT,
	description = 'Default Configuration',
	interfaces = {
		Association{
			bInterfaceClass = USB_CLASS_AUDIO,
			bInterfaceSubClass = 0x0,
			bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
			description = 'Audio Interface Association',
			interfaces = {
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_CONTROL,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 0,
					description = 'USB Sound Device',
					class_specific = audio_control_descriptors,
					endpoints = {}
				},
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_STREAMING,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 0,
					description = 'Audio Capture Zero Bandwidth Interface',
					endpoints = {}
				},
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_STREAMING,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 1,
					description = 'Audio Capture Interface',
					class_specific = audio_streaming_in_descriptors,
					endpoints = {
						EndpointIn{wMaxPacketSize = 200, bInterval = 0x04, bmAttributes = 0x05}
					}
				},
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_STREAMING,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 0,
					description = 'Audio Playback Zero Bandwidth Interface',
					endpoints = {}
				},
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_STREAMING,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 1,
					description = 'Audio Playback Interface',
					class_specific = audio_streaming_out_descriptors,
					endpoints = {
						EndpointOut{wMaxPacketSize = 200, bInterval = 0x04, bmAttributes = 0x05}
					}
				},
			},
		},
    },
}

audio.hs_config = Config{  -- high speed
	bConfigurationValue = 1,
	bmAttributes = USB_CONFIG_SELFPOWERED,
	bMaxPower = USB_MAX_CURRENT,
	description = 'Default Configuration',
	interfaces = {
		Association{
			bInterfaceClass = USB_CLASS_AUDIO,
			bInterfaceSubClass = 0x0,
			bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
			description = 'Audio Interface Association',
			interfaces = {
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_CONTROL,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 0,
					description = 'USB Sound Device',
					class_specific = audio_control_descriptors,
					endpoints = {}
				},
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_STREAMING,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 0,
					description = 'Audio Capture Zero Bandwidth Interface',
					endpoints = {}
				},
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_STREAMING,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 1,
					description = 'Audio Capture Interface',
					class_specific = audio_streaming_in_descriptors,
					endpoints = {
						EndpointIn{wMaxPacketSize = 200, bInterval = 0x04, bmAttributes = 0x05}
					}
				},
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_STREAMING,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 0,
					description = 'Audio Playback Zero Bandwidth Interface',
					endpoints = {}
				},
				Iface{
					bInterfaceClass = USB_CLASS_AUDIO,
					bInterfaceSubClass = USB_AUDIO_SUBCLASS_STREAMING,
					bInterfaceProtocol = USB_AUDIO_PROTOCOL_2_0,
					bAlternateSetting = 1,
					description = 'Audio Playback Interface',
					class_specific = audio_streaming_out_descriptors,
					endpoints = {
						EndpointOut{wMaxPacketSize = 200, bInterval = 0x04, bmAttributes = 0x05}
					}
				},
			},
		},
	},
}
