#pragma once

enum CellStatus { //стан клітинки поля
	empty, //пуста
	deck, //палуба
	kill, //undef
	undef, //невідома клітинка, використовується для "матриці маски"
};