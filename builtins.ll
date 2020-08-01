; ModuleID = 'builtins.c'
source_filename = "builtins.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@.str.4 = private unnamed_addr constant [3 x i8] c"%f\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @writeInteger(i32 %n) #0 {
entry:
  %n.addr = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  %0 = load i32, i32* %n.addr, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32 %0)
  ret void
}

declare dso_local i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @writeBoolean(i1 zeroext %b) #0 {
entry:
  %b.addr = alloca i8, align 1
  %frombool = zext i1 %b to i8
  store i8 %frombool, i8* %b.addr, align 1
  %0 = load i8, i8* %b.addr, align 1
  %tobool = trunc i8 %0 to i1
  %conv = zext i1 %tobool to i32
  %cmp = icmp eq i32 %conv, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i64 0, i64 0))
  br label %if.end

if.else:                                          ; preds = %entry
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0))
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @writeChar(i8 signext %c) #0 {
entry:
  %c.addr = alloca i8, align 1
  store i8 %c, i8* %c.addr, align 1
  %0 = load i8, i8* %c.addr, align 1
  %conv = sext i8 %0 to i32
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i64 0, i64 0), i32 %conv)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @writeReal(double %x) #0 {
entry:
  %x.addr = alloca double, align 8
  store double %x, double* %x.addr, align 8
  %0 = load double, double* %x.addr, align 8
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i64 0, i64 0), double %0)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @readInteger() #0 {
entry:
  %n = alloca i32, align 4
  %call = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* %n)
  %0 = load i32, i32* %n, align 4
  ret i32 %0
}

declare dso_local i32 @__isoc99_scanf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @readBoolean() #0 {
entry:
  %n = alloca i8, align 1
  %call = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i64 0, i64 0), i8* %n)
  %0 = load i8, i8* %n, align 1
  %tobool = icmp ne i8 %0, 0
  ret i1 %tobool
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local signext i8 @readChar() #0 {
entry:
  %n = alloca i8, align 1
  %call = call i32 @getchar()
  %conv = trunc i32 %call to i8
  store i8 %conv, i8* %n, align 1
  %0 = load i8, i8* %n, align 1
  ret i8 %0
}

declare dso_local i32 @getchar() #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @readReal() #0 {
entry:
  %n = alloca double, align 8
  %call = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0), double* %n)
  %0 = load double, double* %n, align 8
  ret double %0
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @ln(double %x) #0 {
entry:
  %x.addr = alloca double, align 8
  store double %x, double* %x.addr, align 8
  %0 = load double, double* %x.addr, align 8
  %call = call double @log(double %0) #4
  ret double %call
}

; Function Attrs: nounwind
declare dso_local double @log(double) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @arctan(double %x) #0 {
entry:
  %x.addr = alloca double, align 8
  store double %x, double* %x.addr, align 8
  %0 = load double, double* %x.addr, align 8
  %call = call double @atan(double %0) #4
  ret double %call
}

; Function Attrs: nounwind
declare dso_local double @atan(double) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @pi() #0 {
entry:
  ret double 0x400921FB54442D18
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @trunc2(double %x) #0 {
entry:
  %x.addr = alloca double, align 8
  store double %x, double* %x.addr, align 8
  %0 = load double, double* %x.addr, align 8
  %1 = call double @llvm.trunc.f64(double %0)
  %conv = fptosi double %1 to i32
  ret i32 %conv
}

; Function Attrs: nounwind readnone speculatable willreturn
declare double @llvm.trunc.f64(double) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @round2(double %x) #0 {
entry:
  %x.addr = alloca double, align 8
  store double %x, double* %x.addr, align 8
  %0 = load double, double* %x.addr, align 8
  %1 = call double @llvm.round.f64(double %0)
  %conv = fptosi double %1 to i32
  ret i32 %conv
}

; Function Attrs: nounwind readnone speculatable willreturn
declare double @llvm.round.f64(double) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local signext i8 @chr(i32 %x) #0 {
entry:
  %x.addr = alloca i32, align 4
  store i32 %x, i32* %x.addr, align 4
  %0 = load i32, i32* %x.addr, align 4
  %conv = trunc i32 %0 to i8
  ret i8 %conv
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @ord(i8 signext %x) #0 {
entry:
  %x.addr = alloca i8, align 1
  store i8 %x, i8* %x.addr, align 1
  %0 = load i8, i8* %x.addr, align 1
  %conv = sext i8 %0 to i32
  ret i32 %conv
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @writeString([0 x i8]* %x) {
writest:
  %x1 = alloca [0 x i8]*, align 8
  store [0 x i8]* %x, [0 x i8]** %x1, align 8
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  %0 = load [0 x i8]*, [0 x i8]** %x1, align 8
  %1 = load i32, i32* %i, align 4
  %2 = getelementptr [0 x i8], [0 x i8]* %0, i32 0, i32 %1
  %3 = load i8, i8* %2, align 1
  %4 = icmp ne i8 %3, 0
  br i1 %4, label %loop, label %after

loop:                                             ; preds = %loop, %writest
  %5 = load [0 x i8]*, [0 x i8]** %x1, align 8
  %6 = load i32, i32* %i, align 4
  %7 = getelementptr [0 x i8], [0 x i8]* %5, i32 0, i32 %6
  %8 = load i8, i8* %7, align 1
  call void @writeChar(i8 %8)
  %9 = load i32, i32* %i, align 4
  %10 = add i32 %9, 1
  store i32 %10, i32* %i, align 4
  %11 = load [0 x i8]*, [0 x i8]** %x1, align 8
  %12 = load i32, i32* %i, align 4
  %13 = getelementptr [0 x i8], [0 x i8]* %11, i32 0, i32 %12
  %14 = load i8, i8* %13, align 1
  %15 = icmp ne i8 %14, 0
  br i1 %15, label %loop, label %after

after:                                            ; preds = %loop, %writest
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @readString(i32 %n, [0 x i8]* %x) {
readst:
  %n1 = alloca i32, align 4
  store i32 %n, i32* %n1, align 4
  %x2 = alloca [0 x i8]*, align 8
  store [0 x i8]* %x, [0 x i8]** %x2, align 8
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  %0 = load i32, i32* %i, align 4
  %1 = load i32, i32* %n1, align 4
  %2 = icmp slt i32 %0, %1
  br i1 %2, label %loop, label %after

loop:                                             ; preds = %loop, %readst
  %3 = call i8 @readChar()
  %4 = load [0 x i8]*, [0 x i8]** %x2, align 8
  %5 = load i32, i32* %i, align 4
  %6 = getelementptr [0 x i8], [0 x i8]* %4, i32 0, i32 %5
  store i8 %3, i8* %6, align 1
  %7 = load i32, i32* %i, align 4
  %8 = add i32 %7, 1
  store i32 %8, i32* %i, align 4
  %9 = load i32, i32* %i, align 4
  %10 = load i32, i32* %n1, align 4
  %11 = icmp slt i32 %9, %10
  br i1 %11, label %loop, label %after

after:                                            ; preds = %loop, %readst
  %12 = load [0 x i8]*, [0 x i8]** %x2, align 8
  %13 = load i32, i32* %i, align 4
  %14 = getelementptr [0 x i8], [0 x i8]* %12, i32 0, i32 %13
  store i8 0, i8* %14, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @cMalloc(i32 %s) #0 {
entry:
  %s.addr = alloca i32, align 4
  store i32 %s, i32* %s.addr, align 4
  %0 = load i32, i32* %s.addr, align 4
  %conv = sext i32 %0 to i64
  %call = call noalias i8* @malloc(i64 %conv) #2
  %1 = ptrtoint i8* %call to i64
  ret i64 %1
}

; Function Attrs: nounwind
declare dso_local noalias i8* @malloc(i64) #1

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone speculatable willreturn }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 11.0.0 (https://github.com/llvm/llvm-project.git 1956a8a7cb79e94dbe073e36eba2d6b003f91046)"}
