# level06

### Magic ✨
```bash
gdb -batch level06 -ex 'b * 0x080487ba' -ex 'b * 0x08048866' -ex 'r' -ex 'set $eax=0x1' -ex 'c' -ex 'p *(int *)($ebp - 0x10)' -ex 'c'
```
(Thanks to [this stackoverflow answer](https://stackoverflow.com/a/46867839))
