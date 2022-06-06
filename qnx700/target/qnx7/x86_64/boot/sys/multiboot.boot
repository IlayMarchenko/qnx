[
default_image=4m
len=0x200
attr="?-bigendian"
vboot=0xffff800000000000
+rsvd_vaddr
filter="mkifsf_elf -m3 -e1 %a %s %i"
]
