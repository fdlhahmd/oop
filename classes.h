#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


using namespace std;

//base class untuk produk yang dijual
class Barang{
	private:
		string nama;
		int harga;
		int stok;
		
	public:
		string getNama(){ return this->nama; }
		void setNama(string nama){ this->nama = nama; }
		
		int getHarga(){ return this->harga; }
		void setHarga(int harga){ this->harga = harga; }
		
		int getStok(){ return this->stok; }		
		void setStok(int stok){ this->stok = stok; }
};

//subclass untuk produk bertipe sparepart
class Sparepart : public Barang{
	private:
		string merk;
	public:
//		constructor untuk class
		Sparepart(string nama, int harga, int stok, string merk){ 
			this->setNama(nama);
			this->setHarga(harga);
			this->setStok(stok);
			this->merk = merk;
		}
		
		string getMerk(){ return this->merk; }
		void setMerk(string merk){ this->merk = merk; }
		
		void print(){
			cout<<this->getNama()<<"\t "<<this->getHarga()<<"\t "<<this->getStok()<<"\t "<<this->getMerk();
		}
};

//subclass untuk produk bertipe aksesoris
class Aksesoris : public Barang{
	private:
		string warna;
	public:
//		constructor untuk class
		Aksesoris(string nama, int harga, int stok,string warna){ 
			this->setNama(nama);
			this->setHarga(harga);
			this->setStok(stok);
			this->setWarna(warna);
		}
		
		string getWarna(){ return this->warna; }
		void setWarna(string warna){ this->warna = warna; }
		
		void print(){
			cout<<this->getNama()<<"\t "<<this->getHarga()<<"\t "<<this->getStok()<<"\t "<<this->getWarna();
		}
};

//class untuk menyimpan data produk yang dibeli dalam suatu pesanan
class OrderItem {
	private:
		int subTotal;
		int jumlah;
		Barang barang;
	public:
//		constructor untuk class
		OrderItem(Barang b, int jumlah){ 
			this->barang = b; 
			this->jumlah = jumlah; 
			this->subTotal = b.getHarga() * jumlah ;
		}
				
		int getSubTotal(){ return this->subTotal; }
		
		void print(){
			cout<<this->barang.getNama()<<" \t"<<this->jumlah<<" \t"<<this->getSubTotal()<<endl;
		}
};

//class untuk memproses suatu pesanan
class Order{
	private:
		string id;
		int total;
//		menyimpan list data produk yang dipesan
		vector<OrderItem> listOrderItems;
		
	public:
		Order(string id){ this->id = id; }
		
//		method untuk menambah produk ke dalam listOrderItems
		void addOrderItem(OrderItem b){
			listOrderItems.push_back(b);
			total += b.getSubTotal();
		}
		
		string getId(){return this->id; }
		
		int getTotalHarga(){ return this->total; }
		void setTotalHarga(int jml){ this->total += jml; }
		
		void print(){
			for (int i = 0; i < listOrderItems.size(); i++){
				OrderItem t = listOrderItems.at(i);
				cout<<i+1<<". \t";
				t.print();
			}
		}
		
//		method untuk memproses order
		void order(vector<Sparepart> gudangSp, vector<Aksesoris> gudangAk){
			int pil = 1;
			int nominal;
			int temp;
			int jumlah;
			
			this->total = 0;
			
			while(pil != 0){
				int i = 0;
				
				system("cls");
				cout<<"\tMenu Pemesanan Barang"<<endl;
				cout<<"-------------------------------"<<endl;
				cout<<"ID Pesanan    : "<< this->getId()<<endl;
				cout<<"-------------------------------"<<endl;
				cout<<"Jumlah Barang : "<< listOrderItems.size() <<endl;
				cout<<"Total Harga   : "<< this->getTotalHarga() <<endl;
				cout<<"==============================="<<endl;
				cout<<"1. Tambah Sparepart"<<endl;
				cout<<"2. Tambah Aksesoris"<<endl;
				cout<<"3. Lihat Keranjang"<<endl;
				cout<<"0. Checkout"<<endl;
				cout<<">>>";
				cin>>pil;
				cout<<endl;
				switch(pil){
					case 1:
					{
//						tampilkan data sparepart dari list yang ada
						cout<<"\tDaftar Sparepart"<<endl;		
						cout<<"-------------------------------"<<endl;
						cout<<"No\tNama\tHarga\tStok\tMerk"<<endl;
						cout<<"-------------------------------"<<endl;
						for (int i = 0; i < gudangSp.size(); i++){
							Sparepart t = gudangSp.at(i);
							cout<<i+1<<". \t";
							t.print();
							cout<<endl;
						}
						
						cout<<"-------------------------------"<<endl;
						cout<<"Masukkan pilihan : ";		
						cin>>temp;
						
						if(temp - 1 < 0 || temp - 1 >= gudangSp.size()){
							cout<<"Pilihan tidak ditemukan"<<endl;		
							break;
						}

//						ambil data barang sesuai inputan yang diterima							
						Barang b = gudangSp.at(temp - 1);
						cout<<"Masukkan jumlah : ";		
						cin>>jumlah;
						
						if(jumlah > b.getStok() || jumlah <= 0){
							cout<<"Jumlah tidak valid"<<endl;
							break;
						}
							
//						masukkan data produk ke dalam listOrderItem
						this->addOrderItem(OrderItem(b, jumlah));
						
//						kurangi jumlah stok
						gudangSp.at(temp - 1).setStok(b.getStok() - jumlah);
						
						break;	
					}
					
					case 2:
					{
//						tampilkan data aksesoris dari list yang ada
						cout<<"\tDaftar Aksesoris"<<endl;		
						cout<<"-------------------------------"<<endl;
						cout<<"No\tNama\tHarga\tStok\tWarna"<<endl;
						cout<<"-------------------------------"<<endl;
						for (int i = 0; i < gudangAk.size(); i++){
							Aksesoris t = gudangAk.at(i);
							cout<<i+1<<". \t";
							t.print();
							cout<<endl;
						}
						
						cout<<"-------------------------------"<<endl;
						cout<<"Masukkan pilihan : ";		
						cin>>temp;
						
						if(temp - 1 < 0 || temp - 1 >= gudangAk.size()){
							cout<<"Pilihan tidak ditemukan"<<endl;		
							break;
						}
							
//						ambil data barang sesuai inputan yang diterima
						Barang b = gudangAk.at(temp - 1);
						cout<<"Masukkan jumlah : ";		
						cin>>jumlah;
						
						if(jumlah > b.getStok() || jumlah <= 0){
							cout<<"Jumlah tidak valid"<<endl;
							break;
						}
							
//						masukkan data produk ke dalam listOrderItem
						this->addOrderItem(OrderItem(b, jumlah));
						
//						kurangi jumlah stok
						gudangAk.at(temp - 1).setStok(b.getStok() - jumlah);
						
						break;	
					}
					
					case 3:
//						menampilkan daftar produk yang telah dipesan
						cout<<"\tDaftar Keranjang"<<endl;		
						cout<<"-------------------------------"<<endl;
						this->print();
						cout<<"-------------------------------"<<endl;
						cout<<"Total Harga   : "<< this->getTotalHarga() <<endl;						
						break;	
						
					case 0:
//						menampilkan daftar produk yang telah dipesan
						cout<<"\tDaftar Keranjang"<<endl;		
						cout<<"-------------------------------"<<endl;
						cout<<"No\tNama\tJumlah\tSubtotal"<<endl;
						cout<<"-------------------------------"<<endl;
						this->print();
						cout<<"-------------------------------"<<endl;
						cout<<"Total Harga \t: "<< this->getTotalHarga() <<endl;
						
//						proses pembayaran
						do{
							cout<<"Masukkan jumlah uang : ";
							cin>>nominal;	
							if(nominal < this->getTotalHarga())
								cout<<"Uang kurang!"<<endl;
						}
						while(nominal < this->getTotalHarga());
						
						cout<<endl<<"Kembalian   		: "<< nominal - this->getTotalHarga() <<endl;												
						break;
				}	
				getch();
			}
		}
};
