; ModuleID = 'inputs/instruction_replace.c'
source_filename = "inputs/instruction_replace.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx15.0.0"

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @foo(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = mul nsw i32 %3, 2
  ret i32 %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @bar(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %5 = load i32, ptr %3, align 4
  %6 = load i32, ptr %4, align 4
  %7 = call i32 @foo(i32 noundef %6)
  %8 = mul nsw i32 %7, 2
  %9 = add nsw i32 %5, %8
  ret i32 %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @fez(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, ptr %4, align 4
  store i32 %1, ptr %5, align 4
  store i32 %2, ptr %6, align 4
  %7 = load i32, ptr %4, align 4
  %8 = load i32, ptr %4, align 4
  %9 = load i32, ptr %5, align 4
  %10 = call i32 @bar(i32 noundef %8, i32 noundef %9)
  %11 = mul nsw i32 %10, 2
  %12 = add nsw i32 %7, %11
  %13 = load i32, ptr %6, align 4
  %14 = mul nsw i32 %13, 3
  %15 = add nsw i32 %12, %14
  ret i32 %15
}

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
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
  store ptr %1, ptr %5, align 8
  store i32 123, ptr %6, align 4
  store i32 0, ptr %7, align 4
  %12 = load i32, ptr %7, align 4
  %13 = load i32, ptr %7, align 4
  %14 = add nsw i32 %12, %13
  store i32 %14, ptr %6, align 4
  store i32 0, ptr %7, align 4
  store i32 60, ptr %8, align 4
  %15 = load i32, ptr %6, align 4
  %16 = call i32 @foo(i32 noundef %15)
  %17 = load i32, ptr %7, align 4
  %18 = add nsw i32 %17, %17
  store i32 %18, ptr %7, align 4
  %19 = load i32, ptr %6, align 4
  %20 = load i32, ptr %7, align 4
  %21 = call i32 @bar(i32 noundef %19, i32 noundef %20)
  %22 = load i32, ptr %7, align 4
  %23 = add nsw i32 %22, %21
  store i32 %23, ptr %7, align 4
  %24 = load i32, ptr %6, align 4
  %25 = load i32, ptr %7, align 4
  %26 = call i32 @fez(i32 noundef %24, i32 noundef %25, i32 noundef 123)
  %27 = load i32, ptr %7, align 4
  %28 = add nsw i32 %27, %26
  store i32 %28, ptr %7, align 4
  %29 = load i32, ptr %9, align 4
  %30 = mul nsw i32 %29, 1
  store i32 %30, ptr %10, align 4
  %31 = load i32, ptr %10, align 4
  %32 = add nsw i32 %31, 0
  store i32 %32, ptr %11, align 4
  %33 = load i32, ptr %7, align 4
  ret i32 %33
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
