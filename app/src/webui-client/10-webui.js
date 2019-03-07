wg.common = {
    
    page(navigationKey, pageTitle, content) {

        let navigation = {
            stations: "Stations",
            settings: "Settings"
        }

        document.title = pageTitle;

        return DIV([
            DIV("navigation",[ 
            DIV("title").text("Retradio"),
            ...Object.entries(navigation).map(([key, title]) => 
                AHREF(key === navigationKey? "active": "", {href: key}).text(title)
            )
            ]), 
            DIV("content", content)
        ]);
    }
}

let activeBand = 0;

wg.pages.stations = {
    async render(container, pageName, pageParams) {
        
        if (pageParams.b !== undefined) {
            activeBand = parseInt(pageParams.b);
        }

        container.append(wg.common.page("stations", "Stations", [
            DIV("bands", async bands => {
                bands.append(
                    (await wg.webui.getStations())
                    .map((band, bandIndex) => DIV("band" + (bandIndex === activeBand? " active": ""), [
                        AHREF("title", {href: `stations?b=${bandIndex}`}).text(`Band ${bandIndex + 1}`),
                        DIV("stations", band.map((station, stationIndex) => DIV("station", [
                            DIV("play").text("play").click(e => {
                                wg.webui.playStation(bandIndex, stationIndex).catch(console.error);
                            }),
                            DIV("name").text(station.name),
                            DIV("url").text(station.url),
                        ])))
                    ]))
                );
            })
        ]));
    }
}

wg.pages.home = wg.pages.stations;

wg.pages.settings = {
    async render(container) {
        container.append(wg.common.page("settings", "Settings", [
            DIV().text("Some settings")
        ]));
    }
}


