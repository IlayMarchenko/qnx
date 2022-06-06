-- Descriptor information for USB Audio 2.0 Device

-- define descriptors .device, .fs_config, and .hs_config table values
-- by assigning each a string of bytes
-- the table value .strings must be a table of strings

USBDC_FULL_SPEED_MPS     = 64
USBDC_HIGH_SPEED_MPS     = 512

USBDC_VENDOR_ID          = 0x1234
USBDC_PRODUCT_ID         = 0xfff1
USBDC_MAX_CURRENT        = 0
USBDC_NUM_CONFIGURATIONS = 1            -- must be 1
USBDC_REVISION           = 0x0200

-- AC_HEADER + (total_clock_sources * clock_source_len) + (total_clock_selectors * clock_selector_len) + (total_input_terminals * input_terminal_len) + (total_output_terminals * output_terminal_size) + (total_class_audio_stream_general * class_audio_stream_general_length) + (total_class_audio_format_type1 * class_audio_format_type1_length)
SIZE_AUDIO_DESCS         = (0x9 + (1 * 0x8) + (1 * 0x8) + (2 * 0x11) + (2 * 0xc) + (2 * 0x10) + (2 * 0x06))

-- config_len + (total_IADs * IAD_len) + (total_interfaces * interface_len) + (total_endpoints * endpoint_len) + (audio descriptors)
SIZE_CONFIG_DESC         = (0x9 + (1 * 0x8) + (5 * 0x9) + (2 * 0x7) + SIZE_AUDIO_DESCS)

audio_raw_desc = {}

audio_raw_desc.device  = string.char(
	0x12,                     -- bLength
	0x01,                     -- bDescriptorType
	0x00,                     -- bcdUSB (LSB)
	0x02,                     -- bcdUSB (MSB)
	0x00,                     -- bDeviceClass
	0x00,                     -- bDeviceSubClass
	0x00,                     -- bDeviceProtocol
	0x40,                     -- bMaxPacketSize
	lsb(USBDC_VENDOR_ID),     -- idVendor (LSB)
	msb(USBDC_VENDOR_ID),     -- idVendor (MSB)
	lsb(USBDC_PRODUCT_ID),    -- idProduct (LSB)
	msb(USBDC_PRODUCT_ID),    -- idProduct (MSB)
	lsb(USBDC_REVISION),      -- bcdDevice (LSB)
	msb(USBDC_REVISION),      -- bcdDevice (MSB)
	0x01,                     -- iManufacturer
	0x02,                     -- iProduct
	0x03,                     -- iSerialNumber
	USBDC_NUM_CONFIGURATIONS  -- bNumConfigurations
)

audio_raw_desc.fs_config = string.char(
-- Configuration Descriptor
	0x9,                    -- bLength
	0x2,                    -- bDescriptorType
	lsb(SIZE_CONFIG_DESC),  -- wTotalLength (LSB)
	msb(SIZE_CONFIG_DESC),  -- wTotalLength (MSB)
	0x03,                   -- bNumInterfaces
	0x01,                   -- bConfigurationValue
	0x04,                   -- iConfiguration
	0xC0,                   -- bmAttributes
	0x00,                   -- max power

-- Audio Interface Association Descriptor
	0x08,                   -- bLength
	0x0B,                   -- bDescriptorType
	0x00,                   -- bFirstInterface
	0x03,                   -- bInterfaceCount
	0x01,                   -- bInterfaceClass
	0x00,                   -- bInterfaceSubClass
	0x00,                   -- bInterfaceProtocol
	0x05,                   -- iFunction

-- Audio Control Interface Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x00,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x00,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x01,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x06,                   -- iInterface

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
	0x01,                   -- bmControls
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

-- Audio Streaming Input Interface (Alternate 0) Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x01,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x00,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x07,                   -- iInterface

-- Audio Streaming Input Interface (Alternate 1) Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x01,                   -- bInterfaceNumber
	0x01,                   -- bAlternateSetting
	0x01,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x08,                   -- iInterface

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

-- Audio Isoch IN Endpoint Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x81,                   -- bEndpointAddress
	0x05,                   -- bmAttributes
	0xc8,                   -- wMaxPacketSize -- 200 bytes
	0x00,                   -- wMaxPacketSize
	0x04,                   -- bInterval

-- Audio Streaming Output Interface (Alternate 0) Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x02,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x00,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x09,                   -- iInterface

-- Audio Streaming Output Interface (Alternate 1) Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x02,                   -- bInterfaceNumber
	0x01,                   -- bAlternateSetting
	0x01,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x0A,                   -- iInterface

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

-- Audio Isoch OUT Endpoint Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x01,                   -- bEndpointAddress
	0x05,                   -- bmAttributes
	0xc8,                   -- wMaxPacketSize -- 200 bytes
	0x00,                   -- wMaxPacketSize
	0x04                    -- bInterval
)

audio_raw_desc.hs_config = string.char(
-- Configuration Descriptor
	0x9,                    -- bLength
	0x2,                    -- bDescriptorType
	lsb(SIZE_CONFIG_DESC),  -- wTotalLength (LSB)
	msb(SIZE_CONFIG_DESC),  -- wTotalLength (MSB)
	0x03,                   -- bNumInterfaces
	0x01,                   -- bConfigurationValue
	0x04,                   -- iConfiguration
	0xC0,                   -- bmAttributes
	0x00,                   -- max power

-- Audio Interface Association Descriptor
	0x08,                   -- bLength
	0x0B,                   -- bDescriptorType
	0x00,                   -- bFirstInterface
	0x03,                   -- bInterfaceCount
	0x01,                   -- bInterfaceClass
	0x00,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x05,                   -- iFunction

-- Audio Control Interface Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x00,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x00,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x01,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x06,                   -- iInterface

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

-- Audio Streaming Input Interface (Alternate 0) Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x01,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x00,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x07,                   -- iInterface

-- Audio Streaming Input Interface (Alternate 1) Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x01,                   -- bInterfaceNumber
	0x01,                   -- bAlternateSetting
	0x01,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x08,                   -- iInterface

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

-- Audio Isoch IN Endpoint Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x81,                   -- bEndpointAddress
	0x05,                   -- bmAttributes
	0xc8,                   -- wMaxPacketSize -- 200 bytes
	0x00,                   -- wMaxPacketSize
	0x04,                   -- bInterval

-- Audio Streaming Output Interface (Alternate 0) Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x02,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x00,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x09,                   -- iInterface

-- Audio Streaming Output Interface (Alternate 1) Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x02,                   -- bInterfaceNumber
	0x01,                   -- bAlternateSetting
	0x01,                   -- bNumEndpoints
	0x01,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass
	0x20,                   -- bInterfaceProtocol
	0x0A,                   -- iInterface

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

-- Audio Isoch OUT Endpoint Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x01,                   -- bEndpointAddress
	0x05,                   -- bmAttributes
	0xc8,                   -- wMaxPacketSize -- 200 bytes
	0x00,                   -- wMaxPacketSize
	0x04                    -- bInterval
)

audio_raw_desc.strings = {
	string.char(4, 3, 9, 4),  -- bLength, bDescriptorType, lsb(wLANGID), msb(wLANGID)
	string.char(26, 3)..double_byte'QNX Software',
	string.char(40, 3)..double_byte'USB Audio Accessory',
	string.char(26, 3)..double_byte'123456789ABC',
	string.char(44, 3)..double_byte'Default Configuration',
	string.char(56, 3)..double_byte'Audio Interface Association',
	string.char(34, 3)..double_byte'USB Sound Device',
	string.char(82, 3)..double_byte'Audio Capture Zero Bandwidth Interface',
	string.char(48, 3)..double_byte'Audio Capture Interface',
	string.char(80, 3)..double_byte'Audio Playback Zero Bandwidth Interface',
	string.char(50, 3)..double_byte'Audio Playback Interface',
}
