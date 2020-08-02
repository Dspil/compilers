; ModuleID = 'pcl program'
source_filename = "pcl program"

declare void @writeInteger(i32)

declare void @writeBoolean(i1)

declare void @writeChar(i8)

declare void @writeReal(double)

declare void @writeString([0 x i8]*)

declare i32 @abs(i32)

declare double @fabs(double)

declare double @sqrt(double)

declare double @sin(double)

declare double @cos(double)

declare double @tan(double)

declare double @arctan(double)

declare double @exp(double)

declare double @ln(double)

declare double @pi()

declare i32 @trunc2(double)

declare i32 @round2(double)

declare i32 @ord(i8)

declare i8 @chr(i32)

declare i32 @readInteger()

declare i1 @readBoolean()

declare i8 @readChar()

declare double @readReal()

declare void @readString(i32, [0 x i8]*)

declare i32 @cMalloc(i64)

define i32 @main() {
entry:
  %x = alloca [5 x i8]*, align 8
  %0 = call i32 @cMalloc(i64 mul nuw (i64 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i64), i64 5))
  %1 = inttoptr i32 %0 to [5 x i8]*
  store [5 x i8]* %1, [5 x i8]** %x, align 8
  %2 = load [5 x i8]*, [5 x i8]** %x, align 8
  %3 = bitcast [5 x i8]* %2 to i8*
  tail call void @free(i8* %3)
  store [5 x i8]* null, [5 x i8]** %x, align 8
  ret i32 0
}

declare void @free(i8*)
