#include <iostream>
#include <iomanip> 
#include <thread>
#include <fstream>
#include <algorithm> 
#include <vector>
#include <stdexcept>
#include <chrono>

using namespace std;


class DinamikDizi
{
public:
	DinamikDizi(int boyut=5)
	{
		m_boyut = boyut;
		m_adres = new int[m_boyut];
		m_kullanilan = 0;

	}

	~DinamikDizi()
	{
		delete[] m_adres;
	}

	int boyut()const 
	{
		return m_boyut;
	}

	int kullanilan()const
	{
		return m_kullanilan;
	}

	int getir(int sira)const
	{
		if (sira<0 || sira>=m_kullanilan)
		{
			throw exception("getir sira hatasi");
		}
		return m_adres[sira];
	}

	void genislet(int ekBoyut)
	{
		int* yeniAdres = new int[m_boyut + ekBoyut];
		for (int i = 0; i < m_kullanilan; i++)
		{
			yeniAdres[i] = m_adres[i];
			
		}
		delete[] m_adres;
		m_adres = yeniAdres;
		m_boyut += ekBoyut;
	}

	friend ostream& operator<<(ostream& os, const DinamikDizi& dizi)
	{
		os << "|";
		for (int i = 0; i < dizi.boyut(); i++)
		{
			os << setw(3) << i << setw(1) << "|";
		}
		os << endl << "|";
		for (int i = 0; i < dizi.boyut(); i++)
		{
			os << setw(3) << "---" << setw(1) << "|";
		}
		os << endl << "|";
		for (int i = 0; i < dizi.kullanilan(); i++)
		{
			os << setw(3) << dizi.getir(i) << setw(1) << "|";
		}
		for (int i = dizi.kullanilan(); i < dizi.boyut(); i++)
		{
			os << setw(3) << "bos" << setw(1) << "|";
		}
		os << endl << "|";

		return os;
	}
	
	void arayaEkle(int sira, int veri)
	{
		if (sira>=0&&sira<=m_kullanilan)
		{
			if (m_kullanilan >= m_boyut)
			{
				genislet(m_boyut);
			}
			for (int i = m_kullanilan-1; i >= sira; i--)
				m_adres[i + 1] = m_adres[i];

			m_adres[sira] = veri;
			m_kullanilan++;
		}
	}

	void sonaEkle(int yeniSayi) 
	{
		arayaEkle(m_kullanilan, yeniSayi);
	}

	void cikar(int sira)
	{
		if (sira >= 0 && m_kullanilan > 0 && sira < m_kullanilan)
		{
			for (int i = sira; i < m_kullanilan - 1; i++)  
			{
				m_adres[i] = m_adres[i + 1];
			}
			m_kullanilan--; 
		}
		else
		{
			throw exception("Sira Hatası!");
		}
	}

	void basaEkle(int yeniSayi)
	{
		if (m_kullanilan >= m_boyut)
		{
			genislet(m_boyut);
		}

		for (int i = m_kullanilan; i > 0; i--)
		{
			m_adres[i] = m_adres[i - 1];
		}

		m_adres[0] = yeniSayi;
		m_kullanilan++;
	}

	void diziyiSirala() {
		for (int i = 0; i < m_kullanilan - 1; i++) {
			for (int j = 0; j < m_kullanilan - i - 1; j++) {
				if (m_adres[j] > m_adres[j + 1]) {
					int temp = m_adres[j];
					m_adres[j] = m_adres[j + 1];
					m_adres[j + 1] = temp;
				}
			}
		}
	}

	int elemanlariTopla() 
	{
		int toplam = 0;
		for (int i = 0; i < m_kullanilan; i++)
		{
			toplam += m_adres[i];
		}
		return toplam;
	}

	void diziyiTemizle() 
	{
		m_kullanilan = 0;
	}

	void diziyiDosyayaYaz(const char* dosyaAdi) const
	{
		ofstream dosya(dosyaAdi);

		if (dosya.is_open())
		{
			for (int i = 0; i < m_kullanilan; i++)
			{
				dosya << m_adres[i] << " ";
			}

			dosya.close();
		}
		else
		{
			throw exception("Dosya acilamadi!");
		}
	}

	
	void diziyiDosyadanOku(const char* dosyaAdi)
	{
		ifstream dosya(dosyaAdi);

		if (dosya.is_open())
		{
			int eleman;
			while (dosya >> eleman)
			{
				sonaEkle(eleman);
			}

			dosya.close();
		}
		else
		{
			throw exception("Dosya acilamadi!");
		}
	}

	
	void elemaniGuncelle(int sira, int yeniDeger)
	{
		if (sira >= 0 && sira < m_kullanilan)
		{
			m_adres[sira] = yeniDeger;
		}
		else
		{
			throw exception("Gecerli bir sira numarasi girin!");
		}
	}
	bool belirliDegeriAra(int deger) const
	{
		for (int i = 0; i < m_kullanilan; i++)
		{
			if (m_adres[i] == deger)
			{
				return true;
			}
		}
		return false;
	}

	vector<int> degeriSaglayanlariFiltrele(int kosul) const
	{
		vector<int> filtrelenmis;
		for (int i = 0; i < m_kullanilan; i++)
		{
			if (m_adres[i] == kosul)
			{
				filtrelenmis.push_back(m_adres[i]);
			}
		}
		return filtrelenmis;
	}

	bool diziyiSiralaVeIkiliArama(int aranan) const
	{
		
		vector<int> siraliDizi(m_adres, m_adres + m_kullanilan);
		sort(siraliDizi.begin(), siraliDizi.end()); // diziyi sıraladık

		// ikili şekilde aradık
		return binary_search(siraliDizi.begin(), siraliDizi.end(), aranan);
	}
private:
	int m_boyut;
	int m_kullanilan;
	int* m_adres;
};

int main()
{
	DinamikDizi dizi;
	while (true)
	{
		system("cls");
		cout << dizi;

		cout << "\n1-Sona Ekle \n";
		cout << "2-Araya Ekle\n";
		cout << "3-Basa Ekle\n";
		cout << "4-Cikar\n";
		cout << "5-Diziyi Sirala\n";
		cout << "6-Elemanlari Topla\n";
		cout << "7-Diziyi Temizle\n";
		cout << "8-Belirli Değeri Ara\n";
		cout << "9-Degeri Saglayanlari Filtrele\n";
		cout << "10-Diziyi Sirala ve Ikili Arama\n";
		cout << "11-Diziyi Dosyaya Yaz\n";
		cout << "12-Diziyi Dosyadan Oku\n";
		cout << "13-Cikis\n";

		int secim;
		cin >> secim;

		switch (secim)
		{
		case 1:
			dizi.sonaEkle(rand() % 101);
			break;
		case 2:
			int sira;
			cout << "sira : ";
			cin >> sira;
			dizi.arayaEkle(sira, rand() % 101);
			break;
		case 3:
			int yeniSayi;
			cout << "Yeni sayi: ";
			cin >> yeniSayi;
			dizi.basaEkle(yeniSayi);
			break;
		case 4:
			int cikarSira;
			cout << "sira : ";
			cin >> cikarSira;
			dizi.cikar(cikarSira);
			break;
		case 5:
			dizi.diziyiSirala();
			break;
		case 6:
			cout << "Toplam = " << dizi.elemanlariTopla() << "   ---- Toplam 7 saniye sonra kaybolucaktir ! " << endl;
			this_thread::sleep_for(chrono::seconds(7));
			break;
		case 7:
			dizi.diziyiTemizle();
			break;
		case 8:
			int arananDeger;
			cout << "Aranan deger: ";
			cin >> arananDeger;
			if (dizi.belirliDegeriAra(arananDeger))
			{
				cout << "Deger bulundu. (5sn sonra kaybolucaktır)" << endl;
				this_thread::sleep_for(chrono::seconds(5));
			}
			else
			{
				cout << "Deger bulunamadi.(5sn sonra kaybolucaktır)" << endl;
				this_thread::sleep_for(chrono::seconds(5));
			}
			break;
		case 9:
			int kosul;
			cout << "Filtreleme kosulu: ";
			cin >> kosul;
			{
				vector<int> filtrelenmis = dizi.degeriSaglayanlariFiltrele(kosul);
				cout << "Filtrelenmis elemanlar: ";
				for (int eleman : filtrelenmis)
				{
					cout << eleman << " ";
				}
				cout << endl;
			}
			break;
		case 10:
			int aramaDegeri;
			cout << "Aranan deger: ";
			cin >> aramaDegeri;
			if (dizi.diziyiSiralaVeIkiliArama(aramaDegeri))
			{
				cout << "Deger bulundu." << endl;
				this_thread::sleep_for(chrono::seconds(5));
			}
			else
			{
				cout << "Deger bulunamadi." << endl;
				this_thread::sleep_for(chrono::seconds(5));
			}
			break;
		case 11:
		{
			const char* dosyaAdiYaz = "dizi.txt";
			dizi.diziyiDosyayaYaz(dosyaAdiYaz);
			cout << "Dizi dosyaya yazildi: " << dosyaAdiYaz << endl;
			break;
		}
		case 12:
		{
			const char* dosyaAdiOku = "dizi.txt";
			dizi.diziyiDosyadanOku(dosyaAdiOku);
			cout << "Dizi dosyadan okundu: " << dosyaAdiOku << endl;
			break;
		}
		case 13:
			return 0;
		default:
			cout << "Geçersiz secim. Tekrar deneyin." << endl;
			break;
		}
	}
}
