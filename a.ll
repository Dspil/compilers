; ModuleID = 'pcl program'
source_filename = "pcl program"

@0 = private unnamed_addr constant [3 x i8] c", \00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@2 = private unnamed_addr constant [16 x i8] c"Initial array: \00", align 1
@3 = private unnamed_addr constant [15 x i8] c"Sorted array: \00", align 1

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
  %i = alloca i32, align 4
  %x = alloca [16 x i32], align 4
  %seed = alloca i32, align 4
  store i32 0, i32* %i, align 4
  store i32 65, i32* %seed, align 4
  %0 = load i32, i32* %i, align 4
  %1 = icmp slt i32 %0, 16
  br i1 %1, label %loop, label %after

loop:                                             ; preds = %loop, %entry
  %2 = load i32, i32* %seed, align 4
  %3 = mul i32 %2, 137
  %4 = add i32 %3, 221
  %5 = load i32, i32* %i, align 4
  %6 = add i32 %4, %5
  %7 = srem i32 %6, 101
  store i32 %7, i32* %seed, align 4
  %8 = load i32, i32* %seed, align 4
  %9 = load i32, i32* %i, align 4
  %10 = getelementptr [16 x i32], [16 x i32]* %x, i32 0, i32 %9
  store i32 %8, i32* %10, align 4
  %11 = load i32, i32* %i, align 4
  %12 = add i32 %11, 1
  store i32 %12, i32* %i, align 4
  %13 = load i32, i32* %i, align 4
  %14 = icmp slt i32 %13, 16
  br i1 %14, label %loop, label %after

after:                                            ; preds = %loop, %entry
  %15 = bitcast [16 x i32]* %x to [0 x i32]*
  call void @PrintArray([0 x i8]* bitcast ([16 x i8]* @2 to [0 x i8]*), [0 x i32]* %15, i32 16)
  %16 = bitcast [16 x i32]* %x to [0 x i32]*
  call void @BubbleSort([0 x i32]* %16, i32 16)
  %17 = bitcast [16 x i32]* %x to [0 x i32]*
  call void @PrintArray([0 x i8]* bitcast ([15 x i8]* @3 to [0 x i8]*), [0 x i32]* %17, i32 16)
  ret i32 0
}

define internal void @BubbleSort([0 x i32]* %x, i32 %n) {
BubbleSort:
  %x1 = alloca [0 x i32]*, align 8
  store [0 x i32]* %x, [0 x i32]** %x1, align 8
  %n2 = alloca i32, align 4
  store i32 %n, i32* %n2, align 4
  %i = alloca i32, align 4
  %changed = alloca i1, align 1
  store i1 true, i1* %changed, align 1
  %0 = load i1, i1* %changed, align 1
  br i1 %0, label %loop, label %after4

loop:                                             ; preds = %after, %BubbleSort
  store i32 0, i32* %i, align 4
  store i1 false, i1* %changed, align 1
  %1 = load i32, i32* %i, align 4
  %2 = load i32, i32* %n2, align 4
  %3 = sub i32 %2, 1
  %4 = icmp slt i32 %1, %3
  br i1 %4, label %loop3, label %after

loop3:                                            ; preds = %merge, %loop
  %5 = load [0 x i32]*, [0 x i32]** %x1, align 8
  %6 = load i32, i32* %i, align 4
  %7 = getelementptr [0 x i32], [0 x i32]* %5, i32 0, i32 %6
  %8 = load i32, i32* %7, align 4
  %9 = load [0 x i32]*, [0 x i32]** %x1, align 8
  %10 = load i32, i32* %i, align 4
  %11 = add i32 %10, 1
  %12 = getelementptr [0 x i32], [0 x i32]* %9, i32 0, i32 %11
  %13 = load i32, i32* %12, align 4
  %14 = icmp sgt i32 %8, %13
  br i1 %14, label %then, label %else

then:                                             ; preds = %loop3
  %15 = load [0 x i32]*, [0 x i32]** %x1, align 8
  %16 = load i32, i32* %i, align 4
  %17 = getelementptr [0 x i32], [0 x i32]* %15, i32 0, i32 %16
  %18 = load [0 x i32]*, [0 x i32]** %x1, align 8
  %19 = load i32, i32* %i, align 4
  %20 = add i32 %19, 1
  %21 = getelementptr [0 x i32], [0 x i32]* %18, i32 0, i32 %20
  call void @swap(i32* %17, i32* %21)
  store i1 true, i1* %changed, align 1
  br label %merge

else:                                             ; preds = %loop3
  br label %merge

merge:                                            ; preds = %else, %then
  %22 = load i32, i32* %i, align 4
  %23 = add i32 %22, 1
  store i32 %23, i32* %i, align 4
  %24 = load i32, i32* %i, align 4
  %25 = load i32, i32* %n2, align 4
  %26 = sub i32 %25, 1
  %27 = icmp slt i32 %24, %26
  br i1 %27, label %loop3, label %after

after:                                            ; preds = %merge, %loop
  %28 = load i1, i1* %changed, align 1
  br i1 %28, label %loop, label %after4

after4:                                           ; preds = %after, %BubbleSort
  ret void
}

define internal void @swap(i32* %x, i32* %y) {
swap:
  %x1 = alloca i32*, align 8
  store i32* %x, i32** %x1, align 8
  %y2 = alloca i32*, align 8
  store i32* %y, i32** %y2, align 8
  %t = alloca i32, align 4
  %0 = load i32*, i32** %x1, align 8
  %1 = load i32, i32* %0, align 4
  store i32 %1, i32* %t, align 4
  %2 = load i32*, i32** %y2, align 8
  %3 = load i32, i32* %2, align 4
  %4 = load i32*, i32** %x1, align 8
  store i32 %3, i32* %4, align 4
  %5 = load i32, i32* %t, align 4
  %6 = load i32*, i32** %y2, align 8
  store i32 %5, i32* %6, align 4
  ret void
}

define internal void @PrintArray([0 x i8]* %msg, [0 x i32]* %x, i32 %n) {
PrintArray:
  %msg1 = alloca [0 x i8]*, align 8
  store [0 x i8]* %msg, [0 x i8]** %msg1, align 8
  %x2 = alloca [0 x i32]*, align 8
  store [0 x i32]* %x, [0 x i32]** %x2, align 8
  %n3 = alloca i32, align 4
  store i32 %n, i32* %n3, align 4
  %i = alloca i32, align 4
  %0 = load [0 x i8]*, [0 x i8]** %msg1, align 8
  call void @writeString([0 x i8]* %0)
  store i32 0, i32* %i, align 4
  %1 = load i32, i32* %i, align 4
  %2 = load i32, i32* %n3, align 4
  %3 = icmp slt i32 %1, %2
  br i1 %3, label %loop, label %after

loop:                                             ; preds = %merge, %PrintArray
  %4 = load i32, i32* %i, align 4
  %5 = icmp sgt i32 %4, 0
  br i1 %5, label %then, label %else

then:                                             ; preds = %loop
  call void @writeString([0 x i8]* bitcast ([3 x i8]* @0 to [0 x i8]*))
  br label %merge

else:                                             ; preds = %loop
  br label %merge

merge:                                            ; preds = %else, %then
  %6 = load [0 x i32]*, [0 x i32]** %x2, align 8
  %7 = load i32, i32* %i, align 4
  %8 = getelementptr [0 x i32], [0 x i32]* %6, i32 0, i32 %7
  %9 = load i32, i32* %8, align 4
  call void @writeInteger(i32 %9)
  %10 = load i32, i32* %i, align 4
  %11 = add i32 %10, 1
  store i32 %11, i32* %i, align 4
  %12 = load i32, i32* %i, align 4
  %13 = load i32, i32* %n3, align 4
  %14 = icmp slt i32 %12, %13
  br i1 %14, label %loop, label %after

after:                                            ; preds = %merge, %PrintArray
  call void @writeString([0 x i8]* bitcast ([2 x i8]* @1 to [0 x i8]*))
  ret void
}
