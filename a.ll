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
  call void @test_write(i32 4)
  call void @writeChar(i8 10)
  ret i32 0
}

define internal void @test_write(i32 %test_write1) {
test_write:
  %test_write12 = alloca i32, align 4
  store i32 %test_write1, i32* %test_write12, align 4
  %0 = load i32, i32* %test_write12, align 4
  %1 = add i32 %0, 1
  store i32 %1, i32* %test_write12, align 4
  %2 = load i32, i32* %test_write12, align 4
  call void @test_write2(i32 %2)
  ret void
}

define internal void @test_write2(i32 %test_write21) {
test_write2:
  %test_write212 = alloca i32, align 4
  store i32 %test_write21, i32* %test_write212, align 4
  %0 = load i32, i32* %test_write212, align 4
  %1 = add i32 %0, 1
  store i32 %1, i32* %test_write212, align 4
  %2 = load i32, i32* %test_write212, align 4
  call void @writeInteger(i32 %2)
  ret void
}