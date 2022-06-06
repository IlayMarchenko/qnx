[
default_image=4m
len=0x21c
notloaded=0x1c
attr="?-bigendian"
vboot=0xffff800000000000
+rsvd_vaddr
filter="mkifsf_elf -m3 -e1 -w kpi %a %s %i"
]
