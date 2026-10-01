#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (v >= 0 && v <= 8) {
		vCell = v;
		return true;
	}


	return false; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (h >= 0 && h <= 10) {
		hCell = h;
		return true;
	}

	return false; // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	///TODO: Implement this function as described in the .h file
	if ((vCell >= 0 && vCell <= 8) && (hCell >= 0 && hCell <= 10)) {
		return true;
	}

	return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it
	

	///TODO: Implement this function as described in the .h file
	int Integer_Cell_Number = (cellPosition.hCell+1) + (11*(8-cellPosition.vCell));


	return Integer_Cell_Number; // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file

	// Note: this class does NOT deal with real coordinates, it deals with the "vCell", "hCell" and "cellNum" instead

	// assuming NumVerticalCells = 9 and NumHorizontalCells = 11 
	// Cell Numbers (CellNum) should be from 1 to 99
	// Numbered from [left-to-right] [bottom-up], as follows:

	// hCell (right):   0    1   ...   10
	// vCell (below):
	//   0             C89  C90  ...  C99
	//   1             C78  C79  ...  C88
	//  ...            ...  ...  ...  ...
	//   7             C12  C13  ...  C22
	//   8             C1   C2   ...  C11

	// In the Grid above, C13 has vCell = 7 and hCell = 1


	// We can calculate the vCell and hCell from the passed cellNum as follows:
	position.SetVCell (8 - (cellNum - 1) / NumHorizontalCells);
	position.SetHCell ( (cellNum - 1) % NumHorizontalCells) ;





	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum (int addedNum){
	/// TODO: Implement this function as described in the .h file

	int Integer_New_Cell_Num; 
	CellPosition Object_New_Position;
		Integer_New_Cell_Num = GetCellNumFromPosition(*this) + addedNum;
		if (Integer_New_Cell_Num >= 1 && Integer_New_Cell_Num <= 99){
			Object_New_Position = GetCellPositionFromNum(Integer_New_Cell_Num);
			SetVCell(Object_New_Position.vCell);
			SetHCell(Object_New_Position.hCell);
		}
		else
			return;

	// Note: this function updates the data members (vCell and hCell) of the calling object

}