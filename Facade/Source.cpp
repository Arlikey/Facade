#include <iostream>
using namespace std;

class CD_Drive {
public:
	void Start() {
		cout << "Устройство чтения оптических дисков: запуск\n";
	}
	void CheckIfDisk() {
		cout << "Устройство чтения оптических дисков: проверка наличия диска\n";
	}

	void Stop() {
		cout << "Устройство чтения дисков: вернуть в исходную позицию\n";
	}
};

class RAM {
public:
	void StartDevices() {
		cout << "Оперативная память: запуск устройств\n";
	}
	void MemoryAnalyze() {
		cout << "Оперативная память: анализ памяти\n";
	}

	void MemoryClear() {
		cout << "Оперативная память: очистка памяти\n";
	}
};

class HDD {
public:
	void Start() {
		cout << "Винчестер: запуск\n";
	}
	void BootSectorCheck() {
		cout << "Винчестер: проверка загрузочного сектора\n";
	}

	void Stop() {
		cout << "Винчестер: остановка устройства\n";
	}

};

class Videocard {
public:
	void Start() {
		cout << "Видеокарта: запуск\n";
	}
	void MonitorCommunicationCheck() {
		cout << "Видеокарта: проверка связи с монитором\n";
	}
	void DataOutput(RAM ram) {
		cout << "Видеокарта: вывод данных об оперативной памяти\n";
	}
	void DataOutput(CD_Drive cd_drive) {
		cout << "Видеокарта: вывод информации об устройстве чтения дисков\n";
	}
	void DataOutput(HDD hdd) {
		cout << "Видеокарта: вывод данных о винчестере\n";
	}

	void ShowMessage() {
		cout << "Видео карта: вывести на монитор данные прощальное сообщение\n";
	}
};

class Power_Unit {
public:
	void Energize() {
		cout << "Блок питания: подать питание\n";
	}
	void Energize(Videocard videocard) {
		cout << "Блок питания: подать питание на видеокарту\n";
	}
	void Energize(RAM ram) {
		cout << "Блок питания: подать питание на оперативную память\n";
	}
	void Energize(CD_Drive cd_drive) {
		cout << "Блок питания: подать питание на устройство чтения дисков\n";
	}
	void Energize(HDD hdd) {
		cout << "Блок питания: подать питание на винчестер\n";
	}

	void Deactivate(Videocard videocard) {
		cout << "Блок питания: прекратить питание видео карты\n";
	}
	void Deactivate(RAM ram) {
		cout << "Блок питания: прекратить питание оперативной памяти\n";
	}
	void Deactivate(CD_Drive cd_drive) {
		cout << "Блок питания: прекратить питание устройства чтения дисков\n";
	}
	void Deactivate(HDD hdd) {
		cout << "Блок питания: прекратить питание винчестера\n";
	}
	void Deactivate() {
		cout << "Блок питания: выключение\n";
	}
};

class Sensors {
public:
	void CheckVoltage() {
		cout << "Датчики: проверить напряжение\n";
	}
	void CheckTemperature(Power_Unit power_unit) {
		cout << "Датчики: проверить температуру в блоке питания\n";
	}
	void CheckTemperature(Videocard videocard) {
		cout << "Датчики: проверить температуру в видеокарте\n";
	}
	void CheckTemperature(RAM ram) {
		cout << "Датчики: проверить температуру в оперативной памяти\n";
	}
	void CheckTemperatureAll() {
		cout << "Датчики: проверить температуру всех систем\n";
	}
};

class Facade {
	Videocard videocard;
	RAM ram;
	HDD hdd;
	CD_Drive cd_drive;
	Power_Unit power_unit;
	Sensors sensors;
public:
	Facade(Videocard video, RAM ram, HDD hdd, CD_Drive cd_drive, Power_Unit power, Sensors sensors) {
		videocard = video;
		this->ram = ram;
		this->hdd = hdd;
		this->cd_drive = cd_drive;
		power_unit = power;
		sensors = sensors;
	}
	void BeginWork() {
		power_unit.Energize();
		sensors.CheckVoltage();
		sensors.CheckTemperature(power_unit);
		sensors.CheckTemperature(videocard);
		power_unit.Energize(videocard);
		videocard.Start();
		videocard.MonitorCommunicationCheck();
		sensors.CheckTemperature(ram);
		power_unit.Energize(ram);
		ram.StartDevices();
		ram.MemoryAnalyze();
		videocard.DataOutput(ram);
		power_unit.Energize(cd_drive);
		cd_drive.Start();
		cd_drive.CheckIfDisk();
		videocard.DataOutput(cd_drive);
		power_unit.Energize(hdd);
		hdd.Start();
		hdd.BootSectorCheck();
		videocard.DataOutput(hdd);
		sensors.CheckTemperatureAll();
	}

	void EndWork() {
		hdd.Stop();
		ram.MemoryClear();
		ram.MemoryAnalyze();
		videocard.ShowMessage();
		cd_drive.Stop();
		power_unit.Deactivate(videocard);
		power_unit.Deactivate(ram);
		power_unit.Deactivate(cd_drive);
		power_unit.Deactivate(hdd);
		sensors.CheckVoltage();
		power_unit.Deactivate();
	}
};

int main() {
	setlocale(LC_ALL, "RU");

	Videocard videocard;
	RAM ram;
	HDD hdd;
	CD_Drive cd_drive;
	Power_Unit power_unit;
	Sensors sensors;

	Facade pc(videocard, ram, hdd, cd_drive, power_unit, sensors);

	pc.BeginWork();

	cout << "\n\n";

	pc.EndWork();

	system("pause");

	return 0;
}