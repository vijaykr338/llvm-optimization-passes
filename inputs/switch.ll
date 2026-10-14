; ModuleID = 'inputs/switch.c'
source_filename = "inputs/switch.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx15.0.0"

@.str = private unnamed_addr constant [25 x i8] c"complex_switch(%d) = %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [31 x i8] c"nested_conditions(15, 8) = %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @complex_switch(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  store i32 0, ptr %3, align 4
  %5 = load i32, ptr %2, align 4
  switch i32 %5, label %28 [
    i32 1, label %6
    i32 2, label %7
    i32 3, label %7
    i32 4, label %20
  ]

6:                                                ; preds = %1
  store i32 10, ptr %3, align 4
  br label %38

7:                                                ; preds = %1, %1
  store i32 20, ptr %3, align 4
  store i32 0, ptr %4, align 4
  br label %8

8:                                                ; preds = %16, %7
  %9 = load i32, ptr %4, align 4
  %10 = load i32, ptr %2, align 4
  %11 = icmp slt i32 %9, %10
  br i1 %11, label %12, label %19

12:                                               ; preds = %8
  %13 = load i32, ptr %4, align 4
  %14 = load i32, ptr %3, align 4
  %15 = add nsw i32 %14, %13
  store i32 %15, ptr %3, align 4
  br label %16

16:                                               ; preds = %12
  %17 = load i32, ptr %4, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, ptr %4, align 4
  br label %8, !llvm.loop !6

19:                                               ; preds = %8
  br label %38

20:                                               ; preds = %1
  store i32 30, ptr %3, align 4
  %21 = load i32, ptr %2, align 4
  %22 = srem i32 %21, 2
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %24, label %27

24:                                               ; preds = %20
  %25 = load i32, ptr %3, align 4
  %26 = add nsw i32 %25, 5
  store i32 %26, ptr %3, align 4
  br label %27

27:                                               ; preds = %24, %20
  br label %38

28:                                               ; preds = %1
  %29 = load i32, ptr %2, align 4
  %30 = mul nsw i32 %29, 5
  store i32 %30, ptr %3, align 4
  br label %31

31:                                               ; preds = %34, %28
  %32 = load i32, ptr %3, align 4
  %33 = icmp sgt i32 %32, 50
  br i1 %33, label %34, label %37

34:                                               ; preds = %31
  %35 = load i32, ptr %3, align 4
  %36 = sub nsw i32 %35, 10
  store i32 %36, ptr %3, align 4
  br label %31, !llvm.loop !8

37:                                               ; preds = %31
  br label %38

38:                                               ; preds = %37, %27, %19, %6
  %39 = load i32, ptr %3, align 4
  ret i32 %39
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @nested_conditions(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 %0, ptr %4, align 4
  store i32 %1, ptr %5, align 4
  %6 = load i32, ptr %4, align 4
  %7 = icmp sgt i32 %6, 10
  br i1 %7, label %8, label %19

8:                                                ; preds = %2
  %9 = load i32, ptr %5, align 4
  %10 = icmp sgt i32 %9, 10
  br i1 %10, label %11, label %15

11:                                               ; preds = %8
  %12 = load i32, ptr %4, align 4
  %13 = load i32, ptr %5, align 4
  %14 = add nsw i32 %12, %13
  store i32 %14, ptr %3, align 4
  br label %36

15:                                               ; preds = %8
  %16 = load i32, ptr %4, align 4
  %17 = load i32, ptr %5, align 4
  %18 = sub nsw i32 %16, %17
  store i32 %18, ptr %3, align 4
  br label %36

19:                                               ; preds = %2
  %20 = load i32, ptr %5, align 4
  %21 = icmp sgt i32 %20, 5
  br i1 %21, label %22, label %26

22:                                               ; preds = %19
  %23 = load i32, ptr %4, align 4
  %24 = load i32, ptr %5, align 4
  %25 = mul nsw i32 %23, %24
  store i32 %25, ptr %3, align 4
  br label %36

26:                                               ; preds = %19
  %27 = load i32, ptr %4, align 4
  %28 = load i32, ptr %5, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %30, label %31

30:                                               ; preds = %26
  br label %33

31:                                               ; preds = %26
  %32 = load i32, ptr %5, align 4
  br label %33

33:                                               ; preds = %31, %30
  %34 = phi i32 [ 1, %30 ], [ %32, %31 ]
  %35 = sdiv i32 %27, %34
  store i32 %35, ptr %3, align 4
  br label %36

36:                                               ; preds = %33, %22, %15, %11
  %37 = load i32, ptr %3, align 4
  ret i32 %37
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 1, ptr %2, align 4
  br label %5

5:                                                ; preds = %14, %0
  %6 = load i32, ptr %2, align 4
  %7 = icmp sle i32 %6, 6
  br i1 %7, label %8, label %17

8:                                                ; preds = %5
  %9 = load i32, ptr %2, align 4
  %10 = call i32 @complex_switch(i32 noundef %9)
  store i32 %10, ptr %3, align 4
  %11 = load i32, ptr %2, align 4
  %12 = load i32, ptr %3, align 4
  %13 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %11, i32 noundef %12)
  br label %14

14:                                               ; preds = %8
  %15 = load i32, ptr %2, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, ptr %2, align 4
  br label %5, !llvm.loop !9

17:                                               ; preds = %5
  %18 = call i32 @nested_conditions(i32 noundef 15, i32 noundef 8)
  store i32 %18, ptr %4, align 4
  %19 = load i32, ptr %4, align 4
  %20 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %19)
  ret i32 0
}

declare i32 @printf(ptr noundef, ...) #1

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }
attributes #1 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 4]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Homebrew clang version 19.1.7"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
