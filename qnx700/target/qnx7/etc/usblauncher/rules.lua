-- USB builtin variables for descriptor parsing. you can override any value if needed
-- [[
USB_CLASS_DEVICE = 0x00
USB_CLASS_AUDIO = 0x01
    USB_AUDIO_SUBCLASS_CONTROL = 0x01
    USB_AUDIO_SUBCLASS_STREAMING = 0x02
        USB_AUDIO_PROTOCOL_1_0 = 0x00
        USB_AUDIO_PROTOCOL_2_0 = 0x20
USB_CLASS_COMMS = 0x02
    USB_COMMS_SUBCLASS_DIRECT_LINE = 0x01
    USB_COMMS_SUBCLASS_MODEM = 0x02
    USB_COMMS_SUBCLASS_TELEPHONE = 0x03
    USB_COMMS_SUBCLASS_MULTICHANNEL = 0x04
    USB_COMMS_SUBCLASS_CAPI_CONTROL = 0x05
    USB_COMMS_SUBCLASS_ETHERNET = 0x06
    USB_COMMS_SUBCLASS_ATM = 0x07
    USB_COMMS_SUBCLASS_WIRELESS_HANDSET = 0x08
    USB_COMMS_SUBCLASS_DEVICE_MGMT = 0x09
    USB_COMMS_SUBCLASS_MOBILE_DIRECT_LINE = 0x0a
    USB_COMMS_SUBCLASS_OBEX = 0x0b
    USB_COMMS_SUBCLASS_NCM  = 0x0d
    USB_COMMS_SUBCLASS_ETHERNET_EMULATION = 0x0c
        USB_COMMS_PROTOCOL_ETHERNET_EMULATION = 0x07
USB_CLASS_HID = 0x03
    USB_HID_SUBCLASS_NONE = 0x00
        USB_HID_PROTOCOL_NONE = 0x00
        USB_HID_PROTOCOL_KEYBOARD = 0x01
        USB_HID_PROTOCOL_MOUSE = 0x02
    USB_HID_SUBCLASS_BOOTINTERFACE = 0x01
USB_CLASS_PHYSICAL = 0x05
USB_CLASS_IMAGING = 0x06
    USB_IMAGING_SUBCLASS_STILL = 0x01
        USB_IMAGING_STILL_PROTOCOL_PTP = 0x01
USB_CLASS_PRINTER = 0x07
USB_CLASS_MASS_STORAGE = 0x08
USB_CLASS_HUB = 0x09
    USB_HUB_PROTOCOL_FULL = 0x00
    USB_HUB_PROTOCOL_HI_SINGLE_TT = 0x01
    USB_HUB_PROTOCOL_HI_MULTIPLE_TT = 0x02
USB_CLASS_CDC_DATA = 0x0a
USB_CLASS_SMART_CARD = 0x0b
USB_CLASS_CONTENT_SECURITY = 0x0d
USB_CLASS_VIDEO = 0x0e
USB_CLASS_DIAGNOSTIC = 0xdc
USB_CLASS_WIRELESS = 0xe0
    USB_WIRELESS_SUBCLASS_RADIO = 0x01
        USB_WIRELESS_PROTOCOL_BLUETOOTH_PI = 0x01
        USB_WIRELESS_PROTOCOL_UWB_RCI = 0x02
        USB_WIRELESS_PROTOCOL_RNDIS = 0x03
    USB_WIRELESS_SUBCLASS_ADAPTER = 0x02
        USB_WIRELESS_PROTOCOL_HOST_WIRE = 0x01
        USB_WIRELESS_PROTOCOL_DEVICE_WIRE = 0x02
        USB_WIRELESS_PROTOCOL_DEVICE_WIRE_ISOCHRONOUS = 0x03
USB_CLASS_MISC = 0xef
USB_CLASS_APPSPEC = 0xef
    USB_APPSPEC_SUBCLASS_FIRMWARE_UPDATE = 0x01
        USB_APPSPEC_PROTOCOL_FIRMWARE_UPDATE = 0x01
    USB_APPSPEC_SUBCLASS_IRDA_BRIDGE = 0x02
        USB_APPSPEC_PROTOCOL_IRDA_BRIDGE = 0x00
    USB_APPSPEC_SUBCLASS_TEST_MEASURE = 0x03
        USB_APPSPEC_PROTOCOL_TMC = 0x00
        USB_APPSPEC_PROTOCOL_USB488 = 0x01
USB_CLASS_VENDOR_SPECIFIC = 0xff
--]]

------------------------------------------------------------------------------

--[[

dofile '/etc/usblauncher/iap2.lua'
dofile '/etc/usblauncher/iap2ncm.lua'
dofile '/etc/usblauncher/umass.lua'

--[[
  You can control how the USB OTG stack will perform role switching by specifying the operating
  mode of the USB root port. Depending on the configuration of your system you could have one to
  many root port (physical or virtual). The first root port is always used to perform role switching
  between host and device mode due to current limitation of the USB stack. Other root port will only  
  support either Host or Device mode. For this reason usblauncher_otg only need to know how
  "root_port_mode_0" is configure with one of the value below:


      USB_MODE_HOST: The root port will only work in host mode. No role swap is supported 
                     in this case and the first DLL pass to the OTG stack is a HCD (Host Controller
                     Driver) with bus ID 0. 

      USB_MODE_DEVICE: The root port only work in device mode (default operating mode). Role swap 
                       can only happens if you have a special device supporting role swap and the
                       root port is a virtual port. The first DLL pass to the USB stack is a DCD
                       (Device Controller Driver) bus ID 0. 

      USB_MODE_OTG: The root port can be configured either in host or device mode. Role swap is
                    supported by enabling the proper DLL and will only work if the first DLL pass    
                    to the USB OTG stack is the DCD (bus ID 0) and the second DLL is the associate
                    HCD (bus ID 1). You can specify more Dll to the USB OTG stack afterwards but
                    usblauncher_otg do not need to know the current operating mode..

  Note: If needed to support multiple OTG root_port on your target you'll need to have one instance of
  the USB OTG stack and usblauncher_otg for each of them.

--]]
--root_port_mode_0=USB_MODE_OTG
-- Note, to ensure responsiveness to USB events (insertions/removals)
-- make the priority of the USB event handling thread higher
-- than the priority of the processing thread.
--evtprio=20
-- Note, to minimize contention with the processing thread, lower the
-- priority of the monitor thread.
--monprio=10

--NOTE: descriptor override support is currently disabled
device_descriptors = { iap2, iap2ncm, umass }

--NOTE: Role swap timeout (in ms) for unsuccessful role swap (or undetected cable removal immediately following device insertion)
role_swap_timeout = 2000

--]]

-- peripheral rules (when QNX target is the USB device)
device(0x1234, 4) { -- these should match the USB descriptors presented to the USB host
	class(USB_CLASS_COMMS, USB_COMMS_SUBCLASS_MODEM, 0) {
		driver"devc-serusb_dcd -e -v -F -s -d iface_list=0,path=/dev/usb/io-usb-otg"
	},
	class(USB_CLASS_MASS_STORAGE)
	{
		driver"devu-umass_client-block -s /dev/usb/io-usb-otg  -l lun=0,iface=0,fname=/dev/ram0"
	}
}

-- To use only when the iPod is the USB host (after USB role swapping)
device(0x1234, 0xfff1) { -- these should match the USB descriptors presented to the USB host, the iPod
	class(USB_CLASS_VENDOR_SPECIFIC, 0xF0, 0x0) {
		driver"mm-ipod -d iap2,config=/etc/mm/iap2.cfg,probe,ppsdir=/pps/services/multimedia/iap2 -a i2c,addr=0x11,path=/dev/i2c99 -t usbdevice,path=/dev/usb/io-usb-otg -l /dev/shmem/iap2.log -vvvvvv";
	}
}
--]]

--[[
-- uncomment the MirrorLink table to enable the request
MirrorLink = {
	version = 0x0101;
	vendor_id = 0xABAB;
	blacklist = {
		{ vid = 0x0781; did = 0x74e0 }; -- SanDisk Sansa Fuze+
		{ vid = 0x0951; did = 0x1624 }; -- Kingston DataTraveler G2
		{ vid = 0x05ac;              }; -- any Apple device
	};
	timeout = 2000;
	ignore  = false;
	stall_reset = false;
}
--]]

------------------------------------------------------------------------------

skip_devices = {
	device(0x0424, 0xec00);
	device(0x0eef, 0x0001);  -- eGalax Inc. USB TouchController
}

foreach (skip_devices) {
	Ignore;  -- don't even attach to these devices
}

-- this entry could be included in the skip_devices table instead
device(0x0e0f, 0x0003) {
	Ignore;
}

char_devices = {
	device(0x0557, 0x2008);  -- ATEN_232A/GUC_232A
	device(0x2478, 0x2008);  -- TRIPP LITE U2009-000-R
	device(0x9710, 0x7720);  -- MOSCHIP 7720
	device(0x0403, 0x6001);  -- FTDI 8U232AM
	device(0x1199, 0x0120);  -- Sierra AirCard U595
	device(0x0681, 0x0040);  -- Siemens HC25
	device(0x1bc7, 0x1003);  -- Telit UC864E
	device(0x067b, 0x2303);  -- Prolific
}

foreach (char_devices) {
	driver"devc-serusb -d vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno)";
}

device(0x2001, 0x3c05) {  -- D-Link DUB-E100 ethernet dongle
	-- if you provide scripts to run on device insertion and removal,
	-- comment out this block and enable the start and removal rules instead
	interface() { -- still publish a PPS object but ignore all interfaces
		Ignore;
	};
--	start"netstart.sh";
--	removal"netfinish.sh";
}

-- UT Bridge Audio HID rules
device(0x2996, 0x0123) { -- these should match the USB descriptors presented to the USB host
    class(USB_CLASS_HID) {
        driver"devu-ut-jack -o -vvvvv -c vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno),iface=$(iface) -s /dev/usb/io-usb-otg"
    };
}

-- basic options for devb-umass
DISK_OPTS  = "blk cache=1m,vnode=384,auto=none,delwri=2:2,rmvto=none,noatime disk name=umass cdrom name=umasscd";
UMASS_OPTS = "umass priority=21";
--UMASS_OPTS = "umass path=/dev/usb/io-usb-otg,priority=21";
--
-- basic options for USB SD card reader
SD_DISK_OPTS = "blk cache=1m,vnode=384,auto=none,delwri=2:2,rmvto=none,noatime disk name=sdumass";
SD_UMASS_OPTS = "umass priority=21,mpoll=2000"; 

-- table of specific MSC devices that can't handle Microsoft descriptor queries
-- By specifying the vid/did, the rule is tried before any generic rules
known_msc = {
	device(0x0781, 0x5567); -- SanDisk Cruzer Blade
}

foreach (known_msc) {
	driver"devb-umass $(DISK_OPTS) $(UMASS_OPTS),vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno),iface=$(iface),ign_remove";
}

--[[
-- example commented out
device(0x5dc, 0xa410) { -- Lexar
	Never;  -- Never match this device.  Handy way to disable a rule.
	class(USB_CLASS_MASS_STORAGE) {
		driver"devb-umass $(DISK_OPTS) $(UMASS_OPTS),vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno),iface=$(iface),ign_remove";
	};
};
--]]

--[[
iAP2 = {
	whitelist = {
		{ vid = 0x05ac; did = 0x1265 }; -- iPod Nano 5.Gen
	};
	retries = 4;
	delay = 250;
};
]]--

-- iPod

product(0x05AC, 0x1200, 0x12FF) {
--    RoleSwap_DigitaliPodOut;
--    RoleSwap_AppleDevice;
--    Probe_iAP2;
-- launch the following drivers if we stay in host mode (and don't role swap)
-- otherwise, role swap is automatic and the mm-ipod rule above is
-- matched after switching stacks.
	class(USB_CLASS_AUDIO, USB_AUDIO_SUBCLASS_CONTROL) {
--        inc_usr_spec_id = unique"/fs/ipod";  -- does rsrcdbmgr_devno_attach
		driver"io-audio -dipod busno=$(busno),devno=$(devno),cap_name=ipod-$(busno)-$(devno)";
	};
	class(USB_CLASS_HID) {
	-- Define a custom function to generate an iAP1 or iAP2 driver command in host mode based on the result of the Probe_iAP2.
	-- If the Probe_iAP2 is not enabled, the custom function will generate the iAP1 driver command.
		custom = function(obj)
			if obj.EXTRA and obj.EXTRA:find('iap::2') then
				-- for iAP2
				return "mm-ipod -diap2,config=/etc/mm/iap2.cfg,ppsdir=/pps/services/multimedia/iap2-$(busno)-$(devno) -ai2c,addr=0x11,path=/dev/i2c99 -tusbhost,busno=$(busno),devno=$(devno),path=/dev/io-usb/io-usb,audio=/dev/snd/ipod-$(busno)-$(devno)";
			else
				-- for iAP1
				return "io-fs-media -dipod,pps=/pps/services/multimedia/iap1-$(busno)-$(devno),transport=usb:busno=$(busno):devno=$(devno):path=/dev/io-usb/io-usb:audio=/dev/snd/ipod-$(busno)-$(devno),darates=+8000:11025:12000:16000:22050:24000,playback,acp=i2c:addr=0x11:path=/dev/i2c99,config=/etc/mm/ipod.cfg";
			end
		end;
		driver"$(custom)";
	};
	class(USB_CLASS_AUDIO, USB_AUDIO_SUBCLASS_STREAMING) {
		Ignore;
	};

-- Ignore all other interfaces
	interface(0,127) {
		Ignore;
	};
};

-- specific MTP rule
--[[
-- example commented out
device(0x054c, 0x03fd) { -- Sony Walkman
	-- 4d 54 50 == 'M' 'T' 'P'
	ms_desc(string.char(0x4d, 0x54, 0x50), "", 1) {
		driver"io-fs-media -dpfs-sony,device=$(busno):$(devno):$(iface)";
	};
};
--]]

-- this example shows how to specify a MS descriptor vendorId
-- it is somewhat redundant because the device vid & did are also given
--[[
-- example commented out
device(0x781, 0x7420) { -- SanDisk sansa
	ms_desc("MTP", "", 0xfe) {
		driver"io-fs-media -dpfs-sansa,device=$(busno):$(devno):$(iface)";
	};
};
--]]

device() {
	class(USB_CLASS_HUB) {
--		start"echo You can launch a script or driver for hub vid $(vendor_id) did $(product_id)."
		Ignore;
	}
}

-- generic MTP rule should proceed generic MSC (mass storage) rule so that it is tried first.
--
-- generic MTP rule

device() {
	ms_desc("MTP") {
		driver"io-fs-media -dpfs,usbpath=/dev/usb/io-usb-otg,device=$(busno):$(devno):$(iface)";
	};
};

-- generic mass storage rule

device() {
	class(USB_CLASS_MASS_STORAGE) {
		driver"devb-umass $(DISK_OPTS) $(UMASS_OPTS),vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno),iface=$(iface),ign_remove";
	};
};

device() {
	class(USB_CLASS_COMMS, USB_COMMS_SUBCLASS_NCM) {
		start"echo NCM interface $(iface)";
	};
};

--[[
-- uncomment the AOA table to enable the probe
AOA = {
	-- list of devices that should not be probed for Android Open Accessory (AOA) protocol version
	-- the list is just an example; you may wish to add more devices
	blacklist = {
		{ vid = 0x05ac;              }; -- Any Apple device
		{ vid = 0x0781; did = 0x5530 }; -- SanDisk Cruzer
		{ vid = 0x04e8; did = 0x5091 }; -- Samsung YP-S3 media player
	};
}

product(0x18d1, 0x2d00, 0x2d05) { -- Google AOA
	interface(0) {
		custom = function(obj)
			if obj.EXTRA and obj.EXTRA:find('aoa::') then
				return "echo AOA busno=$(busno),devno=$(devno)";
			else
				return "echo Error - AOA probe failed busno=$(busno),devno=$(devno)";
			end
		end;
		driver"$(custom)";
	};
};
--]]

------------------------------------------------------------------------------

if verbose >= 3 then
	table.dump(new_conf)
	table.dump(new_conf.flags)
	show_config()
end

------------------------------------------------------------------------------

--[[
-- The system integrator may override 'allow_role_swap' Lua function
-- for flexible rules to allow or block role swap based on
-- properties of the upstream hub, other PPS object properties, global variables,
-- or even external conditions (environment variable, or file contents, etc.)
function allow_role_swap(obj)
	assert(obj, 'no device object provided')

	-- Supported hub vid/did and port number
	local hub_vid = 0x1111
	local hub_did = 0x2222
	local hub_port = 2

	if tonumber(obj.upstream_device_address) == 0 then
		debug('This target requires a special hub to support role swap. Device connected on a root port.')
		return false
	end

	if obj.upstream_hub == nil then
		debug('Device is connected to a hub but its object is nil.')
		return false
	end

	if tonumber(obj.upstream_hub.vendor_id) ~= hub_vid
		or tonumber(obj.upstream_hub.product_id) ~= hub_did then
		debug('The upstream hub must be vendor id %04x product id %04x to support role swap.', hub_vid, hub_did)
		return false
	end

	debug('Found the supported hub immediately upstream')
	if tonumber(obj.upstream_port) ~= hub_port then
		debug('Role swap only supported on port %d of this hub. Connected on port %u.', hub_port, obj.upstream_port)
		return false
	end

	return true
end
--]]
