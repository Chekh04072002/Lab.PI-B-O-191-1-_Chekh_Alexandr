������������ ����� � ������� ����������� ���������� ���������  
����������� ��������������� ���������� ��������������� ���������� ������� �����������  
"�������� ����������� ����������� ��. �. �. �����������"  
������-����������� ��������  
������� ������������ ��������� � �������������  
<br/><br/>  
  
### ����� �� ������������ ������ � 3<br/> �� ���������� "����������������"  
<br/>  
  
�������� 1 ����� ������ 191(1)  
��� ��������� ���������  
����������� ���������� 09.03.04 "����������� ���������"  
<br/>  
  
<table>  
<tr><td>������� ������������<br/> ������� ������������� �������<br/> ������������ ��������� � �������������</td>  
<td>(������)</td>  
<td>������� �.�.</td>  
</tr>  
</table>  
<br/><br/>  
  
�����������, 2019  
  
**���� ������:**  
- **��������� ������ ���������� �������� ������������ ��������� �����;**  
- **��������� ������ ���������� �������� ������������ �������;**  
- **������� ������ ����������� ��������� ���������.**  
  
#### ��� ������  
  
![]([https://sun9-6.userapi.com/c857232/v857232725/b99ce/D..](https://vk.com/away.php?utf=1&to=https%3A%2F%2Fsun9-6.userapi.com%2Fc857232%2Fv857232725%2Fb99ce%2FDQi5V0HeiMs.jpg))  
  
���. 1. �������� ��� �������������  
  
![]([https://sun9-27.userapi.com/c857232/v857232725/b99de/..](https://vk.com/away.php?utf=1&to=https%3A%2F%2Fsun9-27.userapi.com%2Fc857232%2Fv857232725%2Fb99de%2Fyzw8zJtuv4s.jpg))  
  
���. 2. ����  
  
![]([https://sun9-2.userapi.com/c204628/v204628422/484a5/N..](https://vk.com/away.php?utf=1&to=https%3A%2F%2Fsun9-2.userapi.com%2Fc204628%2Fv204628422%2F484a5%2FN46DUXlIHQQ.jpg))  
  
���. 3. ������ ����� include � libbmp.h  
  
![]([https://sun9-3.userapi.com/c857232/v857232422/bb9ec/G..](https://vk.com/away.php?utf=1&to=https%3A%2F%2Fsun9-3.userapi.com%2Fc857232%2Fv857232422%2Fbb9ec%2FG52U9amRvUU.jpg))  
  
���. 4. ��������� � ���������� ����������  
  
������ ��������� ��� ���������� ������������ ������:  
  
```c++  
#include <iostream>
#include "libbmp.h"

int main() {
	char text[10000];
	int position = 0;
	char pol = 0;
	int counter = 0;
	bool end = false;
	BmpImg img;
	int bit;
	img.read("pic10.bmp");
	const int width = img.get_width();
	const int height = img.get_height();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			bit = img.blue_at(j, i);
			pol <<= 1;
			if (bit % 2 == 1) {
				pol++;
			}
			counter++;
			if (counter == 8) {
				text[position] = pol;
					position++;
				counter = 0;
				if (pol == '\0') {
					end = true;
					break;
				}
			}

			bit = img.green_at(j, i);
			pol <<= 1;
			if (bit % 2 == 1) {
				pol++;
			}
			counter++;
			if (counter == 8) {
				text[position] = pol;
				position++;
				counter = 0;
				if (pol == '\0') {
					end = true;
					break;
				}
			}

			bit = img.red_at(j, i);
			pol <<= 1;
			if (bit % 2 == 1) {
				pol++;
			}
			counter++;
			if (counter == 8) {
				text[position] = pol;
				position++;
				counter = 0;
				if (pol == '\0') {
					end = true;
					break;
				}
			}
		}
		if (end)break;
	}
	std::cout << text;
}
```  
  
�������� ��������� � ������� ��������� ���������:  
  
![]([https://sun9-61.userapi.com/c205624/v205624422/445bd/..](https://vk.com/away.php?utf=1&to=https%3A%2F%2Fsun9-61.userapi.com%2Fc205624%2Fv205624422%2F445bd%2F4dMkJWN02Bk.jpg))  
  
���. 5. �����  
  
#### �����: � �������� ������ ���������� �������� ������������ ��������� �����, �������, ������ ������ ����������� ��������� ���������.