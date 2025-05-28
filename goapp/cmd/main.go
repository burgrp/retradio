package main

import (
	"log/slog"
	"os"
	"os/signal"
	"retradio/pkg/common"
	"syscall"
	"time"

	event "github.com/burgrp/go-event/pkg"

	slogor "gitlab.com/greyxor/slogor"

	system "retradio/pkg/system/impl"
	user "retradio/pkg/user/impl"
)

func main() {

	logger := slog.New(slogor.NewHandler(os.Stderr, slogor.SetLevel(slog.LevelDebug), slogor.SetTimeFormat(time.Stamp), slogor.ShowSource()))

	bus := event.NewEventBus("retradio")
	bus.SetLogger(logger)

	system.Init(bus, logger)
	user.Init(bus, logger)

	bus.Unlock()

	bus.Send(common.ApplicationStarted{})

	ch := make(chan os.Signal, 1)
	signal.Notify(ch, syscall.SIGINT, syscall.SIGTERM)
	<-ch

}
