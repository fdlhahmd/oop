#include "classes.h"
#include<time.h>

using namespace std;

// mengisi data produk yang dijual
void isiGudang(vector<Sparepart> *gudangSp, vector<Aksesoris> *gudangAk){
	(*gudangSp).push_back(Sparepart("UNIT COMP,CDI", 575000, 100,"Honda"));
	(*gudangSp).push_back(Sparepart("PROTECTOR, MUFFLER", 33000, 20,"Honda"));
	(*gudangSp).push_back(Sparepart("BELT DRIVE", 120000, 60,"Yamaha"));
	(*gudangSp).push_back(Sparepart("HEADLIGHT UNIT", 125000, 30,"Yamaha"));
	(*gudangSp).push_back(Sparepart("FUSE, MINI(5A)", 1500, 20,"Honda"));
	
	
	(*gudangAk).push_back(Aksesoris("COVER HDL. RR.", 31000, 24,"Hitam"));
	(*gudangAk).push_back(Aksesoris("MIRROR COMP L",37000,19,"Hitam"));
	(*gudangAk).push_back(Aksesoris("MIRROR COMP R",37000,23,"Hitam"));
	(*gudangAk).push_back(Aksesoris("COVER CENTER",2500,12,"Abu"));		
	(*gudangAk).push_back(Aksesoris("COWL, L FR",15000,19,"Kuning"));		
	
}

// membuat random string untuk id pesanan
string generateId(){
	string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	string result = "";
	for(int i = 0; i < 8; i++)
		result += chars[rand()%(chars.size() - 0) + 0];
	return result;
}

int main(){
	
	int pil = 1;
	int kas = 0;
	int temp;
	
	string conf;
	
	srand(static_cast <unsigned int> (time(0)));
	
//	menyimpan daftar pesanan yang telah selesai
	vector<Order> listOrders;
//	menyimpan daftar barang yang dijual
	vector<Sparepart> gudangSp;
	vector<Aksesoris> gudangAk;
	
	isiGudang(&gudangSp,&gudangAk);
	
	while(pil != 0){
		system("cls");
		cout<<"==============================="<<endl;
		cout<<" \tBengkel XYZ"<<endl;
		cout<<"==============================="<<endl;
		cout<<"Total Pemasukan : Rp."<<kas<<endl;
		cout<<"-------------------------------"<<endl;
		cout<<" 1. Penerimaan Order "<<endl;
		cout<<" 2. Pengembalian Barang "<<endl;
		cout<<" 0. Keluar "<<endl;
		cout<<">>>";
		cin>>pil;
		switch(pil){
			case 1:
			{
//				buat instansi dari class Order
				Order ord = Order(generateId());
//				panggil method order
				ord.order(gudangSp, gudangAk);
//				tambahkan instansi ke dalam list setelah method selesai berjalan
				if(ord.getTotalHarga() > 0){
					listOrders.push_back(ord);
					kas+=ord.getTotalHarga();
				}
				break;	
			}
			case 2:
			{
				cout<<endl<<"\tLog Order"<<endl;		
				cout<<"-------------------------------"<<endl;
				cout<<"No\tID Order\tTotal"<<endl;
				cout<<"-------------------------------"<<endl;
				
//				tampilkan semua isi listOrder
				for (int i = 0; i < listOrders.size(); i++){
					Order t = listOrders.at(i);
					cout<<i+1<<".   ";
					cout<<t.getId()<<" \t"<<t.getTotalHarga()<<endl;
				}
				
				cout<<"-------------------------------"<<endl;
				cout<<"Masukkan pilihan : ";		
				cin>>temp;
				
				if(temp - 1 < 0 || temp - 1 >= listOrders.size()){
					cout<<"Pilihan tidak ditemukan"<<endl;		
					break;
				}
				
//				ambil data pesanan sesuai input yang diterima
				Order ord = listOrders.at(temp - 1);
				
//				cetak daftar pesanan
				cout<<endl<<"Daftar Pesanan : "<<ord.getId()<<endl;		
				cout<<"-------------------------------"<<endl;
				ord.print();
				cout<<"-------------------------------"<<endl;
				cout<<"Total Harga   : "<<ord.getTotalHarga() <<endl;						
				
//				minta konfirmasi
				cout<<endl<<"Konfirmasi pengembalian barang untuk pesanan berikut? (y/n)";
				cin>>conf;
				
//				jika terkonfirmasi, kurangi kas toko dan hapus pesanan dari list
				if(conf == "y" || conf == "Y"){
					kas -= ord.getTotalHarga();
					listOrders.erase(listOrders.begin() + temp - 2, listOrders.begin() + temp - 2);
				}
						
				break;	
			}
		}
		getchar();
	}	
	return 0;
}

