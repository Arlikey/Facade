#include <iostream>
using namespace std;

class CD_Drive {
public:
	void Start() {
		cout << "���������� ������ ���������� ������: ������\n";
	}
	void CheckIfDisk() {
		cout << "���������� ������ ���������� ������: �������� ������� �����\n";
	}

	void Stop() {
		cout << "���������� ������ ������: ������� � �������� �������\n";
	}
};

class RAM {
public:
	void StartDevices() {
		cout << "����������� ������: ������ ���������\n";
	}
	void MemoryAnalyze() {
		cout << "����������� ������: ������ ������\n";
	}

	void MemoryClear() {
		cout << "����������� ������: ������� ������\n";
	}
};

class HDD {
public:
	void Start() {
		cout << "���������: ������\n";
	}
	void BootSectorCheck() {
		cout << "���������: �������� ������������ �������\n";
	}

	void Stop() {
		cout << "���������: ��������� ����������\n";
	}

};

class Videocard {
public:
	void Start() {
		cout << "����������: ������\n";
	}
	void MonitorCommunicationCheck() {
		cout << "����������: �������� ����� � ���������\n";
	}
	void DataOutput(RAM ram) {
		cout << "����������: ����� ������ �� ����������� ������\n";
	}
	void DataOutput(CD_Drive cd_drive) {
		cout << "����������: ����� ���������� �� ���������� ������ ������\n";
	}
	void DataOutput(HDD hdd) {
		cout << "����������: ����� ������ � ����������\n";
	}

	void ShowMessage() {
		cout << "����� �����: ������� �� ������� ������ ���������� ���������\n";
	}
};

class Power_Unit {
public:
	void Energize() {
		cout << "���� �������: ������ �������\n";
	}
	void Energize(Videocard videocard) {
		cout << "���� �������: ������ ������� �� ����������\n";
	}
	void Energize(RAM ram) {
		cout << "���� �������: ������ ������� �� ����������� ������\n";
	}
	void Energize(CD_Drive cd_drive) {
		cout << "���� �������: ������ ������� �� ���������� ������ ������\n";
	}
	void Energize(HDD hdd) {
		cout << "���� �������: ������ ������� �� ���������\n";
	}

	void Deactivate(Videocard videocard) {
		cout << "���� �������: ���������� ������� ����� �����\n";
	}
	void Deactivate(RAM ram) {
		cout << "���� �������: ���������� ������� ����������� ������\n";
	}
	void Deactivate(CD_Drive cd_drive) {
		cout << "���� �������: ���������� ������� ���������� ������ ������\n";
	}
	void Deactivate(HDD hdd) {
		cout << "���� �������: ���������� ������� ����������\n";
	}
	void Deactivate() {
		cout << "���� �������: ����������\n";
	}
};

class Sensors {
public:
	void CheckVoltage() {
		cout << "�������: ��������� ����������\n";
	}
	void CheckTemperature(Power_Unit power_unit) {
		cout << "�������: ��������� ����������� � ����� �������\n";
	}
	void CheckTemperature(Videocard videocard) {
		cout << "�������: ��������� ����������� � ����������\n";
	}
	void CheckTemperature(RAM ram) {
		cout << "�������: ��������� ����������� � ����������� ������\n";
	}
	void CheckTemperatureAll() {
		cout << "�������: ��������� ����������� ���� ������\n";
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