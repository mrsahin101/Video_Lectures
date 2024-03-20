# We need to talk about Systemd : Boot Time Optimization for the new init daemon
- Fast way to get fast boot time is use <code>init=/usr/bin/run-qtdemo.sh</code>. But in case of some dependencies, it may not work.

## What is init daemon? 
- **init** is launched by the kernel after it has booted.
- At boot, init has to
    1. start system daemons
    2. configure stuff
    3. restart daemons that have stopped
- Then it sits in the background
    1. Being a parent of the last resort for orphans
    2. Starting daemons that have stopped
    3. Reaping zombies

![Init Deamons](.//Images/Compare.PNG)

## Systemd 
- It is more of way of life, aims to be general purpose system manager
- It has explicit dependencies between services
- Using parallel init, which results in faster boot
- No more shell scripts, which are definetly slow
- Per-daemon resource control. Which results in we can limit cpu, ram usage etc.. which is pretty usefull in embedded systems
- Per-daemon watchdogs

![Init Deamons](.//Images/daemons.PNG)

### Units, services and targets
- **Unit** : Describes a target, a service and several other things
- **Service** : A daemon that can be started and stopped
- **Target** : A group of services similiar to a Sys V runlevel

#### Units
- They are just textfiles
- Systemd searches for units working from most specific to most general configuration
    1. /etc/systemd/system : Local configuration
    2. /run/systemd/system : Runtime configuration
    3. /lib/systemd/system : Distribution-wide configuration

- To override a unit, just place a unit with the same name earlier in the sequence
- To disable a unit, replace it with empty file or a link to /dev/null
- All units have a [Unit] section
- Contains a description, reference to documentation and dependencies n other units
- Example : The Unit section from /lib/systemd/system/dbus.service
``` C
[Unit]
Description=D-Bus System Message Bus
Documentation=man:dbus-daemon(1)
Requires=dbus.socket
[...]
```

#### Units Dependencies
- **Requires** : a list of units this depends on, which should be started before this unit is started
- **Wants** : A weaker form of Requires : This unit is not stopped if any in the list fail to start
- **Conflicts** : A negative dependency: The units listed are stopped when this one is started and conversely, if one of them is started, this one is stopped

#### Order : Before and After
- These keywords determine the order that units are started
- **Before** : This unit should be started before the units listed
- **After** : This unit should be started after the units listed
- Example : Start web server after the network target
``` C
[Unit]
Descriotion=Lighttpd Web Server
After=network.target
[...]
```
- Without Before and After, units are started in no particular order

### Service
- A service is unit that controls a daemon
- Name ends in .service
- Has a [Service] section
- Example, lighttpd.service
``` C
[Unit]
Description=Lighttpd Web Server
After=network.target
[Service]
ExecStart=/usr/sbin/lighttpd -f /etc/lighttpd/lighttpd.conf -D
ExecReload=/bin/kill -HUP $MAINPID
```

### Target
- A target is a Unit that lists dependencies on other targets
- In other saying for target is, its group of services.
- Name ends in .target
- Example, /lib/systemd/system/multi-user.target
``` C
[Unit]
Description=Multi-User System
Documentation=man:systemd.special(7)
Requires=basic.target
Conflicts=rescue.service rescue.target
After=basic.target rescue.service rescue.target
AllowIsolate=yes
```

#### Default Target
- At boot, systemd starts <code>default.target</code>
- Usually a symbolic link to target desired
- Default target may be overriden on kernel command line

### Reverse Dependencies
- **Requires** and **Wants** crate **outgoing** dependencies
    1. Used, for example, to create dependency tree of targets
- Other types of Unit are started **incoming** dependencies
- Incoming dependencies are created by **WantedBy**
- Example : A server that is started by multi-user.target
``` C
[Unit]
Description=Simple server
[Service]
ExecStart=/usr/bin/simpleserver
[Install]
WantedBy=multi-user.target
```
## systemctl
- **systemctl** is commandline interface for systemd
- Useful commands
    1. **start [Unit]** : Start a unit
    2. **stop [Unit]** : Stop a unit
    3. **enable[Unit]** : install the unit, creating the wants link
    4. **disable[Unit]** : uninstall the unit
    5. **status[Unit]** : Show status of a unit
    6. **get-default** : Show default target
    7. **list-dependencies** : list dependency tree

- <code>systemd-analyze</code> is useful tool for measuring systemd boot time

## Another usefull stuff systemd comes with

### Watchdog
- A watchdog will trigger a service to restart on timeout
- Example : Service restarts if no watchdog keepalive is sent within 30s. If it restarts 4 times in 5 minutes will force a reboot
``` C
[Unit]
...
[Service]
WatchdogSec=30s
Restart=on-watchdog
StartLimitInterval=5min
StartLimitBurst=4
StartLimitAction=reboot-force
```

### Resource limits
- Limits system resources that a program can consume
- Example, service with CPU quota %25 and memory limit 4MB
``` C
[Unit]
...
[Service]
ExecStart=/usr/bin/simpleserver
CPUQuota=20%
MemoryAccounting=true
MemoryMax=4096K
```