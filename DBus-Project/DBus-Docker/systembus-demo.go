package main

import (
	"log"

	"github.com/godbus/dbus"
	"github.com/godbus/dbus/introspect"
)

const intro = `
<node>
    <interface name="com.github.guelfey.Demo">
        <method name="Foo">
            <arg direction="out" type="s"/>
        </method>
    </interface>` + introspect.IntrospectDataString + `</node> `

const introRoot = `
<node>
    <interface name="com.github.guelfey.Demo">
        <method name="systemFoo">
            <arg direction="out" type="s"/>
        </method>
    </interface>` + introspect.IntrospectDataString + `</node> `

type foo string

func main() {
	conn, err := dbus.SystemBus()
	if err != nil {
		log.Fatalln(err)
	}
	reply, err := conn.RequestName("com.bluesky.system", dbus.NameFlagDoNotQueue)
	if err != nil {
		log.Fatalln(err)
	}
	if reply != dbus.RequestNameReplyPrimaryOwner {
		log.Fatalln("system.powermanager already registered")
	}
	f := foo("Bar!")
	err = conn.Export(f, "/com/bluesky/system", "com.bluesky.system")
	if err != nil {
		log.Fatalln("export powermanager:", err)
	}
	err = conn.Export(introspect.Introspectable(introRoot), "/com/bluesky/system", "org.freedesktop.DBus.Introspectable")
	if err != nil {
		log.Fatalln("export powermanager (introspectable-root):", err)
	}
	err = conn.Export(introspect.Introspectable(intro), "/com/bluesky/session", "org.freedesktop.DBus.Introspectable")
	if err != nil {
		log.Fatalln("export powermanager (introspectable):", err)
	}
}
