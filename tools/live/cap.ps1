param([string]$Out = "$PSScriptRoot\pcsx2_cap.png")
# Capture the PCSX2 main window at full physical resolution (per-monitor DPI aware).
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System; using System.Runtime.InteropServices;
public class WC {
 [DllImport("user32.dll")] public static extern IntPtr SetThreadDpiAwarenessContext(IntPtr c);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out R r);
 [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr dc, uint f);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EP cb, IntPtr l); public delegate bool EP(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint p);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, System.Text.StringBuilder s, int n);
 [StructLayout(LayoutKind.Sequential)] public struct R { public int L,T,Rr,B; } }
"@
# -4 = DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
[WC]::SetThreadDpiAwarenessContext([IntPtr](-4)) | Out-Null
$pp = (Get-Process pcsx2-qt).Id
$hs = New-Object System.Collections.ArrayList
[WC]::EnumWindows({param($h,$l) $p=0;[WC]::GetWindowThreadProcessId($h,[ref]$p)|Out-Null; if($p -eq $pp -and [WC]::IsWindowVisible($h)){ $sb=New-Object Text.StringBuilder 256; [WC]::GetWindowText($h,$sb,256)|Out-Null; if($sb.ToString() -like 'Shadow Hearts*'){[void]$hs.Add($h)} }; $true},[IntPtr]::Zero) | Out-Null
$h = $hs[0]; $r = New-Object WC+R; [WC]::GetWindowRect($h,[ref]$r) | Out-Null
$w = $r.Rr-$r.L; $ht = $r.B-$r.T
$bmp = New-Object Drawing.Bitmap $w,$ht
$g = [Drawing.Graphics]::FromImage($bmp); $dc = $g.GetHdc()
[WC]::PrintWindow($h,$dc,2) | Out-Null
$g.ReleaseHdc($dc); $g.Dispose()
$bmp.Save($Out); "$w x $ht -> $Out"
