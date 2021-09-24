PCD8544 SÜRÜCÜLÜ LCD ATmega(328 ve 2560) KÜTÜPHANESİ
____________________________________________________
MAKROLAR:

y(sütunlar) için kullanılabilir makrolar:
	line_0 0
	line_1 1
	line_2 2
	line_3 3
	line_4 4

____________________________________________________
FONKSİYONLAR:
    
void LCD_reset(void) : 
	LCD'nin RST pininde reset pulse oluşturur.LCD ile iletişim kurulmadan önce LCD_reset fonsiyonu 
	kullanılmalıdır.

void LCD_init(volatile uint8_t *ddr_addr, volatile uint8_t *port_addr, uint8_t RST_bit, uint8_t DC_bit):
	LCD_reset() fonsiyonundan hemen sonra kullanılmalıdır.LCD nin CLK,MOSI,CE pinleri master cihazın
	zaten ilgili pinlerine bağlanacağından bu pinler için argüman alınmaz.RST ve DC pinlerinin hangi
	pinlere bağlanacağı önemli olmadığından fonksiyon bu pinler için argüman almaktadır.*ddr_addr, bu 
	pinlerin bağlanacağı data direct register adresi içindir.*port_addr, ilgili port adresi içindir.
	RST_bit ve DC_bit, ilgili pinlerin bağlandığı port bitleri içindir.
 
void LCD_command(uint8_t command) : 
	LCD'nin çalışma voltajı, sıcaklık katsayısı, pixel tersleme, adresleme türü gibi tüm ayarlamalar 
	bu fonsiyon ile yapılır ve makro fonksiyonları argüman alır.

void LCD_data(uint8_t data) : 
	Veriler bu fonksiyonlar aracılığıyla gönderilir.1 bytelık datayı argüman olarak alır.

void LCD_clear_coor(uint8_t x1_coor, uint8_t x2_coor, uint8_t y_line) : 
	Herhangi bir satır için istenen sütun aralığında pixelleri temizler.Örneğin x1_coor=0 , x2_coor=2 ve
	y_line=3 için LCD'nin 3 indisli satırında 0-2 sütunları arasındaki tüm pixelleri temizler.Bu örnek 
	için her satır, herbiri 1 bytelık 84 sütundan oluştuğundan 0-2 sütunlarında 
	8(bir y satırı için pxel sayısı)x4(sütun sayısı) = 32 pixeli silecektir.

void LCD_clear(void) : 
	Tüm pixelleri temizler.

void LCd_contrast(uint8_t contrast) : 
	0 ile 0x7F arasında dğer alabilir.

void LCD_invers(uint8_t status) : 
	status argümanı 0 değilse tüm pixelleri tersler.Normal moda dönmek için status argümanının sıfırdan farklı
	olması gerekir.

void LCD_text(char *data, uint8_t x, uint8_t y): 
	Yadırılacak string adresi *data argümanı ile alınır.Yazdırılacak konum, satır için x(0-83) ve sütun 
	için y(0-5) argümanları ile alınır. 
__________________________________________________________________________________________________________________		            		
