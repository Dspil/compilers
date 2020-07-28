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
  %x = alloca [5 x [5 x i32]], align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca i32, align 4
  store i32 0, i32* %i, align 4
  %i1 = load i32, i32* %i, align 4
  %0 = icmp slt i32 %i1, 5
  br i1 %0, label %loop, label %after12

loop:                                             ; preds = %after, %entry
  store i32 0, i32* %j, align 4
  %j2 = load i32, i32* %j, align 4
  %1 = icmp slt i32 %j2, 5
  br i1 %1, label %loop3, label %after

loop3:                                            ; preds = %loop3, %loop
  %i4 = load i32, i32* %i, align 4
  %2 = mul i32 5, %i4
  %j5 = load i32, i32* %j, align 4
  %3 = add i32 %2, %j5
  %i6 = load i32, i32* %i, align 4
  %4 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %x, i32 0, i32 %i6
  %j7 = load i32, i32* %j, align 4
  %5 = getelementptr [5 x i32], [5 x i32]* %4, i32 0, i32 %j7
  store i32 %3, i32* %5, align 4
  %j8 = load i32, i32* %j, align 4
  %6 = add i32 %j8, 1
  store i32 %6, i32* %j, align 4
  %j9 = load i32, i32* %j, align 4
  %7 = icmp slt i32 %j9, 5
  br i1 %7, label %loop3, label %after

after:                                            ; preds = %loop3, %loop
  %i10 = load i32, i32* %i, align 4
  %8 = add i32 %i10, 1
  store i32 %8, i32* %i, align 4
  %i11 = load i32, i32* %i, align 4
  %9 = icmp slt i32 %i11, 5
  br i1 %9, label %loop, label %after12

after12:                                          ; preds = %after, %entry
  store i32 0, i32* %i, align 4
  %i13 = load i32, i32* %i, align 4
  %10 = icmp slt i32 %i13, 5
  br i1 %10, label %loop14, label %after25

loop14:                                           ; preds = %after22, %after12
  store i32 0, i32* %j, align 4
  %j15 = load i32, i32* %j, align 4
  %11 = icmp slt i32 %j15, 5
  br i1 %11, label %loop16, label %after22

loop16:                                           ; preds = %merge, %loop14
  %i17 = load i32, i32* %i, align 4
  %12 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %x, i32 0, i32 %i17
  %j18 = load i32, i32* %j, align 4
  %13 = getelementptr [5 x i32], [5 x i32]* %12, i32 0, i32 %j18
  %14 = load i32, i32* %13, align 4
  call void @writeInteger(i32 %14)
  %j19 = load i32, i32* %j, align 4
  %15 = icmp slt i32 %j19, 4
  br i1 %15, label %then, label %else

then:                                             ; preds = %loop16
  call void @writeChar(i8 44)
  call void @writeChar(i8 32)
  br label %merge

else:                                             ; preds = %loop16
  call void @writeChar(i8 10)
  br label %merge

merge:                                            ; preds = %else, %then
  %j20 = load i32, i32* %j, align 4
  %16 = add i32 %j20, 1
  store i32 %16, i32* %j, align 4
  %j21 = load i32, i32* %j, align 4
  %17 = icmp slt i32 %j21, 5
  br i1 %17, label %loop16, label %after22

after22:                                          ; preds = %merge, %loop14
  %i23 = load i32, i32* %i, align 4
  %18 = add i32 %i23, 1
  store i32 %18, i32* %i, align 4
  %i24 = load i32, i32* %i, align 4
  %19 = icmp slt i32 %i24, 5
  br i1 %19, label %loop14, label %after25

after25:                                          ; preds = %after22, %after12
  ret i32 0
}
