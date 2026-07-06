/******************************************************************************
 * Tên file: HethongDanhgiaKQHT.cpp
 * Tác giả: Nguyễn
 * Ngày tạo: 30/04/2026
 * Mô tả: Chương trình tính kết quả học tập dựa trên các thông tin môn học nhập vào.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

void thongtinmon(int &tinC, double &hsTX1, double &hsTX2, double &hsKTHP, double &TX1, double &TX2, double &KTHP, double &dm ){ //Nhập vào thông tin môn học

	cout << " Nhap so tin chi mon hoc nay: "; cin >> tinC;	
	cout << endl;
		// Nhập hệ số các điểm thường xuyên
	cout << " Nhap he so diem thuong xuyen 1: "; cin >> hsTX1;
	cout << " Nhap he so diem thuong xuyen 2: "; cin >> hsTX2;
	cout << " Nhap he so diem KTHP: "; cin >> hsKTHP;
	
	cout << endl;
	
		// Nhập điểm thi của các đầu điểm
	cout << " Nhap diem thi thuong xuyen 1: "; cin >> TX1;
	cout << " Nhap diem thi thuong xuyen 2: "; cin >> TX2;
	cout << " Nhap diem thi KTHP: "; cin >> KTHP;
	
	cout << endl;

	// Tính tổng điểm của môn đó và quy đổi ra thang 4
	dm = (hsTX1*TX1) + (hsTX2*TX2) + (hsKTHP*KTHP);
}

void quydoipoint(double &diem4, string &diemC, double &dm, int &tcA, int &tcBplus, int &tcF, int &tinC,  bool &co_mon_duoi30, bool &co_mon_duoi25, bool &k_mon_naoF, int &drl){ // Quy đổi điểm sang thang 4 và chữ 
	
	if(dm >= 8.5 && dm <= 10){ // A
		diem4 = 4;
		diemC = "A";
		tcA += tinC;
		drl += 2;	
	}
	else if(dm >= 8.0 && dm <= 8.4){ // B+
		diem4 = 3.5;
		diemC = "B+";
		tcBplus += tinC;
	}
	else if(dm >= 7.0 && dm <= 7.9){ // B
		diem4 = 3;
		diemC = "B";
	}
	else if(dm >= 6.5 && dm <= 6.9){ // C+
		diem4 = 2.5;
		diemC = "C+";
		co_mon_duoi30 = true;
	}
	else if(dm >= 5.5 && dm <= 6.4){ // C
		diem4 = 2;
		diemC = "C";
		co_mon_duoi25 = true;
	}
	else if(dm >= 5.0 && dm <= 5.4){ // D+
		diem4 = 1.5;
		diemC = "D+";
		co_mon_duoi25 = true;
		drl -= 5;
	}
	else if(dm >= 4.0 && dm <= 4.9){ // D
		diem4 = 1;
		diemC = "D";
		co_mon_duoi25 = true;
		drl -= 5;
	}
	else{							  // F
		diem4 = 0;
		diemC = "F";
		tcF += tinC;
		k_mon_naoF = false;
		drl -= 10;
	}	
}

string xep_hang_hocluc(double GPA,  bool &co_mon_duoi30, bool &co_mon_duoi25, bool &k_mon_naoF, int &tcA, int &tcBplus,int &tcF, double tong_tc, string &xl){
	
	double yc_tc1 = (double)(tcA/tong_tc) * 100;
	double yc_tc2 = (double)(tcBplus/tong_tc) * 100;	
	double yc_tc3 = (double)(tcF/tong_tc) * 100;
	
	if( GPA >= 3.6 && k_mon_naoF == true && co_mon_duoi30 == false && co_mon_duoi25 == false && yc_tc1 >= 50){
		xl = " Xuat xac ";
		return " Xuat xac ";
	}
	else if( GPA >= 3.2 && k_mon_naoF == true && co_mon_duoi25 == false && yc_tc2 >= 40){
		xl = " Gioi ";
		return " Gioi ";
	}
	else if( GPA >= 2.5 && k_mon_naoF == true){
		xl = " Kha ";
		return " Kha ";
	}
	else if( GPA >= 2.0 && yc_tc3 >= 20){
		xl = " Trung binh ";
		return " Trung binh ";
	}
	else{
		xl = " Yeu ";
		return " Yeu ";
	}
}

string waring_hocvu( double &GPA, int &tcF, int tong_tc){
	if( GPA < 2.0 || ( tcF/tong_tc )*100 > 30 ){
		return " Canh bao hoc vu lan 1!";
	}
	else if( GPA < 1.5 || ( tcF/tong_tc )*100 > 50 ){
		return " Canh bao hoc vu lan 2!";
	}
	else if( GPA < 1.0 || ( tcF/tong_tc )*100 >= 70){
		return " Buoc thoi hoc!";
	}
	else{
		return "Khong!";
	}
}

int hoc_bong(string &xl, int drl, bool co_mon_duoi30, bool co_mon_duoi25, bool k_mon_naoF, double GPA ){
	
	if( xl == " Xuat xac " && drl >= 105 && co_mon_duoi30 == false && co_mon_duoi25 == false && k_mon_naoF == true){
		return 100;
	}
	else if( xl == " Gioi " || xl == " Xuat xac " && drl >= 100 && co_mon_duoi25 == false && k_mon_naoF == true){
		return 50;
	}
	else if( xl != " Trung binh " && xl != " Yeu " && drl >= 95 && GPA >= 3.0){
		return 30;
	}
}

void xh_diem(double &TX2, double &KTHP, int &tienbo){
	if( KTHP > TX2){
		tienbo++;
	}
}

string phanloai_diem(int m, int &tienbo){
	double ti_le = ( (double)m/tienbo ) * 100;
	if(ti_le >= 70){
		return " Tien bo tot ";
	}
	else if(ti_le >= 50 && ti_le <=69){
		return " On dinh ";
	}
	else if(ti_le >= 30 && ti_le <=49){
		return " Can co gang ";
	}
	else if( ti_le < 30 ){
		return " Thoi thoai ";
	}	
}

int main (){
	
	cout << "====================================================" << endl;
	cout << "|     HE THONG DANH GIA KET QUA HOC TAP SV DH !    |" << endl;
	cout << "====================================================" << endl;
	int n;
	cout << endl;
	cout << " Nhap so luong sinh vien: "; cin >> n;
	cout << endl;
	
	ofstream ghifile;
    ghifile.open("KetQuaHocTap.txt", ios::app);
	while( n-- ){	// Khai báo thông tin từng học sinh
		
		// Dùng để tính GPA
		double tong_diem = 0;
		double tong_tc = 0;
		
		// Dùng để tính học lực
		int tcA = 0;
		int tcBplus = 0;
		int tcF = 0;
		bool co_mon_duoi30 = false;
		bool co_mon_duoi25 = false;
		bool k_mon_naoF = true;
			
		// Dùng để xét học bổng
		int drl = 100;
		float cc_tb = 0;
		string xl = "";
		
		// Dùng để phân tích xu hướng điểm
		int tienbo = 0;
		
		string s;
		cin.ignore();		
		cout << " Nhap ten hoc sinh: "; getline(cin, s);
		cout << endl;
		int m;
		cout << " Nhap so luong mon cua ki: "; cin >> m;		
		cout << endl;
		
		for(int j = 1; j<=m; j++){	// Khai báo thông tin từng môn học
			
			string l;	// LESSON
			cout << " Nhap ten mon hoc " << j << ":"; 
			cin.ignore();			
			getline(cin, l);
			
			cout << " 	||				|| " << endl;
			
			int tinC;
			double hsTX1, hsTX2, hsKTHP, TX1, TX2, KTHP, dm;
			thongtinmon(tinC, hsTX1, hsTX2, hsKTHP, TX1, TX2, KTHP, dm);
			xh_diem(TX2, KTHP, tienbo);
			// Quy đổi ra thang điểm số 4
			double diem4;
			string diemC;
			quydoipoint(diem4, diemC, dm, tcA, tcBplus, tcF, tinC, co_mon_duoi30, co_mon_duoi25, k_mon_naoF, drl);
			
			// In ra tong ket mon hoc 
			cout << endl;
			cout << " Mon " << j << " - " << l << ": Diem = " << dm << "(" << diemC <<")" << " - "<< tinC << " tin chi." << endl;
			
			// Tổng điểm và Tổng tín chỉ của môn học
			tong_diem += (diem4 * tinC);
			tong_tc += tinC;
			cout << endl;
			cc_tb = cc_tb + TX1 + TX2;
		}
		
		if( (cc_tb/m) < 8){
			drl -= 10;
		}
		if( k_mon_naoF == true){
			drl +=3;
		}
		
		double GPA = (double)tong_diem/tong_tc;
			
		if (ghifile.is_open()) {
		ghifile << " Danh gia sinh vien: " << s << " !";
		ghifile << endl;
		ghifile << " ------ " << endl;
		ghifile << "*" <<" GPA: " << GPA << "/4.0" << endl;
		ghifile << "*" <<" Xep loai: " <<  xep_hang_hocluc( GPA, co_mon_duoi30, co_mon_duoi25, k_mon_naoF, tcA, tcBplus, tcF, tong_tc, xl) << endl;
		ghifile << "*" <<" Diem ren luyen: " << drl << "/110" << endl;
		ghifile << "*" << " Xu huong: " << phanloai_diem( m, tienbo ) << endl;
		ghifile << "*" <<" Hoc bong: " << hoc_bong(xl, drl, co_mon_duoi30, co_mon_duoi25, k_mon_naoF, GPA ) << "%" << endl;
		ghifile << "*" <<" Canh bao: " << waring_hocvu( GPA, tcF, tong_tc) << endl; 
		}
	}
	ghifile.close(); // Đóng file sau khi kết thúc chương trình
    cout << "\n==> DA LUU DU LIEU VAO FILE KetQuaHocTap.txt!" << endl;
	return 0;
}

/* CHUAN BI UPDATE LAI LOGIC ^^*/
