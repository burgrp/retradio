package user

type Station struct {
	Name string `yaml:"name"`
	URL  string `yaml:"url"`
}

type Settings struct {
	Stations [][]Station `yaml:"stations"`
	Tuning   struct {
		Set     int `yaml:"set"`
		Station int `yaml:"station"`
	} `yaml:"tuning"`
}

type SettingsChanged *Settings
type SaveSettings *Settings
