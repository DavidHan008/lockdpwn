﻿#ExternalChecksum("..\..\..\ViewControl3D.xaml","{406ea660-64cf-4c82-b6f0-42d48172a799}","AF5930F5E06980D7DF70FDF02E02C4D7")
'------------------------------------------------------------------------------
' <auto-generated>
'     This code was generated by a tool.
'     Runtime Version:4.0.30319.42000
'
'     Changes to this file may cause incorrect behavior and will be lost if
'     the code is regenerated.
' </auto-generated>
'------------------------------------------------------------------------------

Option Strict Off
Option Explicit On

Imports System
Imports System.Diagnostics
Imports System.Windows
Imports System.Windows.Automation
Imports System.Windows.Controls
Imports System.Windows.Controls.Primitives
Imports System.Windows.Data
Imports System.Windows.Documents
Imports System.Windows.Forms.Integration
Imports System.Windows.Ink
Imports System.Windows.Input
Imports System.Windows.Markup
Imports System.Windows.Media
Imports System.Windows.Media.Animation
Imports System.Windows.Media.Effects
Imports System.Windows.Media.Imaging
Imports System.Windows.Media.Media3D
Imports System.Windows.Media.TextFormatting
Imports System.Windows.Navigation
Imports System.Windows.Shapes
Imports System.Windows.Shell


'''<summary>
'''ViewControl3D
'''</summary>
<Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>  _
Partial Public Class ViewControl3D
    Inherits System.Windows.Controls.UserControl
    Implements System.Windows.Markup.IComponentConnector
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",8)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents grid3D As System.Windows.Controls.Grid
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",10)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents ViewPort3D As System.Windows.Controls.Viewport3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",12)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Camera1 As System.Windows.Media.Media3D.PerspectiveCamera
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",14)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents World As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",29)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents ball As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",73)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents link As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",153)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents link2 As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",233)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Tire As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",789)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Strut As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",964)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Axis As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",1215)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Bushing As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",1314)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Axis_X As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",1565)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Axis_Y As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",1816)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Axis_Z As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",2067)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Axis_RX As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",2831)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Axis_RY As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",3595)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Axis_RZ As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4359)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Triangle As System.Windows.Media.Media3D.ModelVisual3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4375)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents TriangleModel As System.Windows.Media.Media3D.GeometryModel3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4405)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents TrianglePnts As System.Windows.Media.Media3D.MeshGeometry3D
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4417)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents ListBox1 As System.Windows.Controls.ListBox
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4418)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Button1 As System.Windows.Controls.Button
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4419)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Button4 As System.Windows.Controls.Button
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4420)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Button5 As System.Windows.Controls.Button
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4421)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents RadioButton1 As System.Windows.Controls.RadioButton
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4422)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents RadioButton2 As System.Windows.Controls.RadioButton
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\..\ViewControl3D.xaml",4423)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Border1 As System.Windows.Controls.Border
    
    #End ExternalSource
    
    Private _contentLoaded As Boolean
    
    '''<summary>
    '''InitializeComponent
    '''</summary>
    <System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")>  _
    Public Sub InitializeComponent() Implements System.Windows.Markup.IComponentConnector.InitializeComponent
        If _contentLoaded Then
            Return
        End If
        _contentLoaded = true
        Dim resourceLocater As System.Uri = New System.Uri("/ViewControl3D;component/viewcontrol3d.xaml", System.UriKind.Relative)
        
        #ExternalSource("..\..\..\ViewControl3D.xaml",1)
        System.Windows.Application.LoadComponent(Me, resourceLocater)
        
        #End ExternalSource
    End Sub
    
    <System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0"),  _
     System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never),  _
     System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes"),  _
     System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity"),  _
     System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")>  _
    Sub System_Windows_Markup_IComponentConnector_Connect(ByVal connectionId As Integer, ByVal target As Object) Implements System.Windows.Markup.IComponentConnector.Connect
        If (connectionId = 1) Then
            Me.grid3D = CType(target,System.Windows.Controls.Grid)
            
            #ExternalSource("..\..\..\ViewControl3D.xaml",8)
            AddHandler Me.grid3D.MouseUp, New System.Windows.Input.MouseButtonEventHandler(AddressOf Me.OnViewportMouseUp)
            
            #End ExternalSource
            
            #ExternalSource("..\..\..\ViewControl3D.xaml",8)
            AddHandler Me.grid3D.MouseDown, New System.Windows.Input.MouseButtonEventHandler(AddressOf Me.OnViewportMouseDown)
            
            #End ExternalSource
            
            #ExternalSource("..\..\..\ViewControl3D.xaml",8)
            AddHandler Me.grid3D.MouseMove, New System.Windows.Input.MouseEventHandler(AddressOf Me.OnViewportMouseMove)
            
            #End ExternalSource
            Return
        End If
        If (connectionId = 2) Then
            Me.ViewPort3D = CType(target,System.Windows.Controls.Viewport3D)
            Return
        End If
        If (connectionId = 3) Then
            Me.Camera1 = CType(target,System.Windows.Media.Media3D.PerspectiveCamera)
            Return
        End If
        If (connectionId = 4) Then
            Me.World = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 5) Then
            Me.ball = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 6) Then
            Me.link = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 7) Then
            Me.link2 = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 8) Then
            Me.Tire = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 9) Then
            Me.Strut = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 10) Then
            Me.Axis = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 11) Then
            Me.Bushing = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 12) Then
            Me.Axis_X = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 13) Then
            Me.Axis_Y = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 14) Then
            Me.Axis_Z = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 15) Then
            Me.Axis_RX = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 16) Then
            Me.Axis_RY = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 17) Then
            Me.Axis_RZ = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 18) Then
            Me.Triangle = CType(target,System.Windows.Media.Media3D.ModelVisual3D)
            Return
        End If
        If (connectionId = 19) Then
            Me.TriangleModel = CType(target,System.Windows.Media.Media3D.GeometryModel3D)
            Return
        End If
        If (connectionId = 20) Then
            Me.TrianglePnts = CType(target,System.Windows.Media.Media3D.MeshGeometry3D)
            Return
        End If
        If (connectionId = 21) Then
            Me.ListBox1 = CType(target,System.Windows.Controls.ListBox)
            Return
        End If
        If (connectionId = 22) Then
            Me.Button1 = CType(target,System.Windows.Controls.Button)
            Return
        End If
        If (connectionId = 23) Then
            Me.Button4 = CType(target,System.Windows.Controls.Button)
            Return
        End If
        If (connectionId = 24) Then
            Me.Button5 = CType(target,System.Windows.Controls.Button)
            Return
        End If
        If (connectionId = 25) Then
            Me.RadioButton1 = CType(target,System.Windows.Controls.RadioButton)
            Return
        End If
        If (connectionId = 26) Then
            Me.RadioButton2 = CType(target,System.Windows.Controls.RadioButton)
            Return
        End If
        If (connectionId = 27) Then
            Me.Border1 = CType(target,System.Windows.Controls.Border)
            Return
        End If
        Me._contentLoaded = true
    End Sub
End Class

