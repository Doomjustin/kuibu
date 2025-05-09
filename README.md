# Toy Projects

## 备忘
cmake的辅助函数
```shell
target_set_warnings(app ENABLE ALL AS_ERROR ALL DISABLE Annoying)
target_enable_lto(app optimized)
copy_dlls_for_debug(app "" "")
```