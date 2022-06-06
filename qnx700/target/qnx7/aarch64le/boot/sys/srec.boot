[
#
# Boot image attributes for an S-record format image.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
filter="mkifsf_srec %a %I %i"
+rsvd_vaddr
vboot=0xffffff8060000000
pagesizes=4k
]
