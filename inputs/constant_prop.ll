; ModuleID = 'inputs/constant_prop.c'
source_filename = "inputs/constant_prop.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx15.0.0"

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @main(i32 noundef %0, ptr noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
  store ptr %1, ptr %5, align 8
  store i32 246, ptr %6, align 4
  %13 = load i32, ptr %6, align 4
  %14 = load i32, ptr %6, align 4
  %15 = add nsw i32 %13, %14
  store i32 %15, ptr %7, align 4
  %16 = load i32, ptr %7, align 4
  %17 = load i32, ptr %7, align 4
  %18 = mul nsw i32 %16, %17
  store i32 %18, ptr %8, align 4
  %19 = load i32, ptr %6, align 4
  %20 = load i32, ptr %6, align 4
  %21 = xor i32 %19, %20
  store i32 %21, ptr %9, align 4
  %22 = load i32, ptr %6, align 4
  %23 = icmp slt i32 22, 3
  br i1 %23, label %24, label %28

24:                                               ; preds = %2
  %25 = load i32, ptr %6, align 4
  %26 = load i32, ptr %6, align 4
  %27 = and i32 %25, %26
  store i32 %27, ptr %9, align 4
  br label %32

28:                                               ; preds = %2
  %29 = load i32, ptr %6, align 4
  %30 = load i32, ptr %6, align 4
  %31 = or i32 %29, %30
  store i32 %31, ptr %9, align 4
  br label %32

32:                                               ; preds = %28, %24
  %33 = load i32, ptr %10, align 4
  %34 = mul nsw i32 %33, 1
  store i32 %34, ptr %11, align 4
  %35 = load i32, ptr %11, align 4
  %36 = add nsw i32 %35, 0
  store i32 %36, ptr %12, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a,+zcm,+zcz" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 4]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Homebrew clang version 19.1.7"}
