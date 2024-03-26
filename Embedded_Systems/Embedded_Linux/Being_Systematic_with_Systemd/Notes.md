# Being Systematic with Systemd

## Concepts
- Bootstrapping a computer is best expressed as a hierarchy
    1. Some things can't start until other things have been started
    2. By expressing dependencies between things you create a tree structure
    3. systemd just needs to walk the tree to reach a goal, called a **target**
- Meta information is written in a simple form, called a **unit**
- Daemons are represented as **service** units

## Systemd in Yocto Project
- Out-of-the-box, Yocto Project uses SystemV init daemon
- To switch to systemd, add this to a suitable conf file
- conf/local.conf : <code>INIT_MANAGER = "systemd"</code>
- Default target is launced at boot, when systemd starts default.target

## Preinstalling services in Yocto
- You want some services to be enabled in the system image
- In Yocto, this is handled by the systemd classs
``` C
simpledaemon.bb
[...]
inherit systemd
SYSTEMD_SERVICE:${PN} = "simpledaemon.service"
[...]
```

## Loading services on demand
- The **socket** unit waits for some event, then starts a service when the event is triggered
- Name ends in **.socket**
- Example, **foo.socket** : 
``` C
[Unit]
Description= Start foo.service when a connection is received from TCP port 1234
[Socket]
ListenStream=1234
Accept=no
[Install]
WantedBy=sockets.target
```
## Timers
- A timer unit is similar to a socket, except the event is time triggered
- foo.timer
``` C
[Unit]
Description=Wait 30 seconds before running foo.service
[Timer]
OnActiveSec= 30sec
[Install]
WantedBy=timers.target
```
