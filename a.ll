; ModuleID = 'pcl program'
source_filename = "pcl program"

declare void @writeInteger(i32)

declare void @writeBoolean(i8)

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

declare i32 @trunc(double)

declare i32 @round(double)

declare i32 @ord(i8)

declare i8 @chr(i32)

declare i32 @readInteger()

declare i8 @readBoolean()

declare i8 @readChar()

declare double @readReal()

declare void @readString(i32, i8*)

define i32 @main() {
entry:
  call void @writeReal(double 3.500000e+00)
  ret i32 0
}
