; ModuleID = 'pcl program'
source_filename = "pcl program"

declare void @writeInteger(i32)

declare void @writeBoolean(i1)

declare void @writeChar(i8)

declare void @writeReal(double)

declare void @writeString(i8*)

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

declare void @readString(i32, i8*)

define i32 @main() {
entry:
  %0 = call i32 @add(i32 10, i32 11, i32 12)
  call void @writeInteger(i32 %0)
  call void @writeChar(i8 10)
  ret i32 0
}

define internal i32 @add(i32 %x, i32 %y, i32 %z) {
add:
  %x1 = alloca i32, align 4
  store i32 %x, i32* %x1, align 4
  %y2 = alloca i32, align 4
  store i32 %y, i32* %y2, align 4
  %z3 = alloca i32, align 4
  store i32 %z, i32* %z3, align 4
  %result = alloca i32, align 4
  %0 = load i32, i32* %x1, align 4
  %1 = load i32, i32* %y2, align 4
  %2 = add i32 %0, %1
  %3 = load i32, i32* %z3, align 4
  %4 = add i32 %2, %3
  store i32 %4, i32* %result, align 4
  %5 = load i32, i32* %result, align 4
  ret i32 %5
}
