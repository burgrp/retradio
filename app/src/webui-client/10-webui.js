wg.common = {

    page(navigationKey, pageTitle, content) {

        let navigation = {
            stations: "Stations",
            settings: "Settings"
        }

        document.title = pageTitle;

        return DIV([
            DIV("navigation", [
                DIV("title").text("Retradio"),
                ...Object.entries(navigation).map(([key, title]) =>
                    AHREF(key === navigationKey ? "active" : "", { href: key }).text(title)
                )
            ]),
            DIV("content", content)
        ]);
    },

    showError(e) {
        alert(e.message || e);
    }
}

wg.pages.stations = {
    async render(container) {

        container.append(wg.common.page("stations", "Stations", [
            DIV("bands", async bands => {

                wg.webui.getStations().then(stations => {

                    bands.append([
                        DIV("switch", stations.map((band, bandIndex) =>
                            DIV("band" + (bandIndex === 0 ? " active" : "")).text(bandIndex + 1).click(e => {
                                bands.find(".active").removeClass("active");
                                bands.find(`.band:nth-child(${bandIndex + 1})`).addClass("active");
                            }))
                        ),
                        DIV("list", stations.map((band, bandIndex) =>
                            DIV("band" + (bandIndex === 0 ? " active" : ""),
                                stations[bandIndex].map((station, stationIndex) => DIV("station", [
                                    DIV("button").click(e => {
                                        wg.webui.playStation(bandIndex, stationIndex).catch(console.error);
                                    }),
                                    DIV("name").text(station.name).click(e => {
                                        let editor = DIV("editor", [
                                            INPUT("name", { type: "text", autofocus: "" }).val(station.name),
                                            INPUT("url", { type: "url" }).val(station.url),
                                            DIV("buttons", [
                                                BUTTON("confirm").text("Save").click(() => {
                                                    station.name = stationDiv.find("input.name").val();
                                                    station.url = stationDiv.find("input.url").val();
                                                    console.info(stations);
                                                    closeEditor();
                                                }),
                                                BUTTON().text("Cancel").click(closeEditor),
                                            ])
                                        ]).hide();

                                        function closeEditor() {
                                            let nameDiv = stationDiv.find("div.name").text(station.name);
                                            editor.fadeOut(() => {
                                                editor.remove();
                                                nameDiv.fadeIn();
                                            });
                                        }

                                        let stationDiv = $(e.target).parent();
                                        stationDiv.find(".name").fadeOut(() => {
                                            stationDiv.append(editor);
                                            editor.fadeIn();
                                        });
                                    })
                                ]))
                            ))
                        )
                    ]);

                }, wg.common.showError);
            })
        ]));
    }
}

wg.pages.home = wg.pages.stations;

wg.pages.settings = {
    async render(container) {
        container.append(wg.common.page("settings", "Settings", [
            DIV("settings", [
                DIV("section", [
                    DIV("caption").text("Software update"),
                    DIV("updates", async div => {

                        async function checkForUpdates() {
                            div.empty().append(DIV("working").text("Checking for updates..."));
                            let updates = await wg.webui.checkForUpdates();
                            div.empty();
                            if (!updates.length) {
                                div.append(DIV("uptodate").text("Software is up to date."));
                            } else {
                                div.append(DIV("log", updates.map(logLine => DIV("line", [
                                    DIV("date").text(new Date(logLine.date).toLocaleDateString()),
                                    DIV("message").text(logLine.message)
                                ])))).append(BUTTON().text("Download updates").click(async () => {
                                    div.empty().append(DIV("working").text("Downloading updates..."));
                                    try {
                                        await wg.webui.downloadUpdates();
                                        await checkForUpdates();
                                    } catch (e) {
                                        div.empty().append(DIV("error").text(e.message || e));
                                    }
                                }));
                            }
                        }
                        await checkForUpdates();

                    })
                ])
            ])
        ]));
    }
}


