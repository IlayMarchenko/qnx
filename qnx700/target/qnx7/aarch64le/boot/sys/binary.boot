[
#
# Boot image attributes for plain binary image.
#
# Assumes that control is passed to the startup entry point after loading.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
+rsvd_vaddr
vboot=0xffffff8060000000
pagesizes=4k
]
