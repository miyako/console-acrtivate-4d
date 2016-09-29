# console-activate-4d
Activate 4D v16 from the command line

###Introduction

See [4d-plugin-activate](https://github.com/miyako/4d-plugin-activate) for background history.

###Usuage

```sh
activate-4d
```

```sh
activate-4d -p "C:\Program Files\4D\4D v16.0\4D Preview\4D.exe"
```

The program simply finds a window that has the class name ``XTB_MAIN_MDI_58A2D9EE`` and activates it.

Optionally, you can specify another class name (``-c``).

You can also pass a full path (``-p``) for disambiguation.

