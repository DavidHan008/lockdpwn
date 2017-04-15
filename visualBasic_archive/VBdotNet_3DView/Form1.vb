Imports System.Windows.Media.Media3D

Public Class Form1
    Private m3DView As ViewControl3D
    Dim pnts(0 To 16) As Vector3D
    Dim selectedHPnt
    Dim nBushdirection As Integer = 0
    Private WithEvents myTimer As New System.Windows.Forms.Timer()

    Private Sub myTimer_Tick() Handles myTimer.Tick
        m3DView.UpdateHardPointVisualModel()
    End Sub
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        m3DView = ElementHost1.Child()


        pnts(0).X = -23 : pnts(0).Y = 393 : pnts(0).Z = -159
        pnts(1).X = -38.376 : pnts(1).Y = 762.342 : pnts(1).Z = -171.74
        pnts(2).X = 279.096 : pnts(2).Y = 350.079 : pnts(2).Z = -140.73
        pnts(3).X = 94.4 : pnts(3).Y = 749 : pnts(3).Z = -115.8
        pnts(4).X = 171 : pnts(4).Y = 383.5 : pnts(4).Z = -105
        pnts(5).X = 0.753 : pnts(5).Y = 658.639 : pnts(5).Z = 320.257
        pnts(6).X = -22.019 : pnts(6).Y = 641 : pnts(6).Z = 52.6
        pnts(7).X = 16 : pnts(7).Y = 609 : pnts(7).Z = 510
        pnts(8).X = -28.992 : pnts(8).Y = 796.885 : pnts(8).Z = -30.072
        pnts(9).X = -29 : pnts(9).Y = 698.004 : pnts(9).Z = -30.939
        pnts(10).X = 43 : pnts(10).Y = 472 : pnts(10).Z = 12
        pnts(11).X = 357 : pnts(11).Y = 325 : pnts(11).Z = -95.6
        pnts(12).X = 13.059 : pnts(12).Y = 611.455 : pnts(12).Z = 474.908
        pnts(13).X = 171 : pnts(13).Y = 242 : pnts(13).Z = -105
        pnts(14).X = -4.59 : pnts(14).Y = 596.24 : pnts(14).Z = 261.88
        pnts(15).X = -118.63 : pnts(15).Y = 590.22 : pnts(15).Z = -70.29
        pnts(16).X = 98.415 : pnts(16).Y = 330 : pnts(16).Z = -76.298
        m3DView.SetHardPoint(17, pnts)
        m3DView.SetCamInitPos1(New Vector3D(1, 1, -1))

        m3DView.addModel("LowerControlArm", 2, True, New Vector3D(15, 15, 15), 1, 3)
        m3DView.addModel("LowerControlArm", 2, True, New Vector3D(15, 15, 15), 2, 3)
        m3DView.addModel("LowerControlArm", 2, True, New Vector3D(15, 15, 15), 2, 1)
        m3DView.addModel("TieRod", 2, True, New Vector3D(15, 15, 15), 4, 5)
        m3DView.addModel("StrutPiston", 4, True, New Vector3D(150, 150, 150), 7, 8)
        m3DView.addModel("Wheel_Knuckle", 5, True, New Vector3D(30, 30, 30), 2, 9)
        m3DView.addModel("Wheel_Knuckle", 5, True, New Vector3D(30, 30, 30), 4, 9)
        m3DView.addModel("Wheel_Knuckle", 5, True, New Vector3D(30, 30, 30), 7, 9)

        m3DView.addModel("Bush_LCAF", 6, True, New Vector3D(30, 30, 30), 1, 3, 0, 3, 2, 1, New Vector3D(0, 0, 0))
        m3DView.addModel("Bush_LCAR", 6, True, New Vector3D(30, 30, 30), 3, 1, 0, -3, 2, 1, New Vector3D(0, -90, 0))
 
        m3DView.addModel("Wheel", 1, True, New Vector3D(360, 600, 600), 9, 10, 0, 1, 0, 2, New Vector3D(0, 0, 0))

        selectedHPnt = 0

        myTimer.Interval = 100
        myTimer.Start()

        ' m3DView.addModel("Bush_Strut_Top", 6, 8, 8, 7, 3, 0, 0, New Vector3D(80, 80, 30), New Vector3D(0, 0, 0))
        ''        m3DView.addModel("Bush_SubFront", 6, 10, 7, 2, New Vector3D(30, 30, 30))
        ''       m3DView.addModel("Bush_SubRear", 6, 11, 11, 0, New Vector3D(30, 30, 30))
        'm3DView.addModel("Bush_TieIn", 6, 5, 5, 4, 3, 0, 0, New Vector3D(30, 30, 30), New Vector3D(0, 0, 0))
        'm3DView.addModel("R_LowerControlArm", 2, New Vector3D(15, 15, 15), -1, -3)
        'm3DView.addModel("R_LowerControlArm", 2, New Vector3D(15, 15, 15), -2, -3)
        'm3DView.addModel("R_LowerControlArm", 2, New Vector3D(15, 15, 15), -2, -1)
        'm3DView.addModel("R_TieRod", 2, New Vector3D(15, 15, 15), -4, -5)
        'm3DView.addModel("R_StrutPiston", 4, New Vector3D(150, 150, 150), -7, -8)
        'm3DView.addModel("R_Wheel_Knuckle", 5, New Vector3D(30, 30, 30), -2, -9)
        'm3DView.addModel("R_Wheel_Knuckle", 5, New Vector3D(30, 30, 30), -4, -9)
        'm3DView.addModel("R_Wheel_Knuckle", 5, New Vector3D(30, 30, 30), -7, -9)

        'm3DView.addModel("R_Bush_LCAF", 6, New Vector3D(30, 30, 30), -1, -3, 0, 3, -2, 1, New Vector3D(0, 0, 0))
        'm3DView.addModel("R_Bush_LCAR", 6, New Vector3D(30, 30, 30), -3, -1, 0, -3, -2, 1, New Vector3D(-90, 0, 0))

        'm3DView.SetCamInitPos2(pnts(9), New Vector3D(1, 1, 1), 1000.0)
        'm3DView.addModel("R_Wheel", 1, New Vector3D(360, 600, 600), -9, -10, 0, 3, 0, 0)


        '        1 LCA Front                          = 	-23	393	-159	
        '2 LCA Ball Joint                     = 	-38.376	762.342	-171.74	
        '3 LCA Rear                           = 	279.096	350.079	-140.73	
        '4 Tie Outter                         = 	94.4	749	-115.8	
        '5 Tie Inner                          = 	171	383.5	-105	
        '6 Bottom of Spring                   = 	0.753	658.639	320.257	
        '7 Bottom of Strut                    = 	-22.019	641	52.6	
        '8 Top Strut                          = 	16	609	510	
        '9 Wheel Center                       = 	-28.992	796.885	-30.072	
        '10 Spindle cv Joint Point            = 	-29	698.004	-30.939	
        '11 Subframe Front                    = 	43	472	12	
        '12 Subframe Rear                     = 	357	325	-95.6	
        '13 Top of Spring                     = 	13.059	611.455	474.908	
        '14 Rack Housing Mount                = 	171	242	-105	
        '15:     Stab'bar Droplink to Strut        = 	-4.59	596.24	261.88	
        '16:     Stab'bar to Droplink              = 	-118.63	590.22	-70.29	
        '16:     Stab'bar Mount Bushing            = 	98.415	330	-76.298	

    End Sub

    Private Sub ElementHost1_ChildChanged(ByVal sender As System.Object, ByVal e As System.Windows.Forms.Integration.ChildChangedEventArgs)

    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If (selectedHPnt < 16) Then
            selectedHPnt = selectedHPnt + 1
        Else
            selectedHPnt = 0
        End If
        Label1.Text = selectedHPnt
        m3DView.SelectHardPoint(selectedHPnt)
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        If (selectedHPnt > 0) Then
            selectedHPnt = selectedHPnt - 1
        Else
            selectedHPnt = 16
        End If
        Label1.Text = selectedHPnt
        m3DView.SelectHardPoint(selectedHPnt)

    End Sub

    Private Sub Label1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Label1.Click

    End Sub

    Private Sub ElementHost1_ChildChanged_1(sender As System.Object, e As System.Windows.Forms.Integration.ChildChangedEventArgs) Handles ElementHost1.ChildChanged

    End Sub

    Private Sub Label3_Click(sender As System.Object, e As System.EventArgs) Handles Label3.Click

    End Sub

    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        If (nBushdirection < 6) Then
            nBushdirection = nBushdirection + 1
        Else
            nBushdirection = 0
        End If

        m3DView.testvalue = nBushdirection

        Select Case nBushdirection
            Case 0
                Label4.Text = "Axis"
            Case 1
                Label4.Text = "Axis_X"
            Case 2
                Label4.Text = "Axis_Y"
            Case 3
                Label4.Text = "Axis_Z"
            Case 4
                Label4.Text="Axis_RX"
            Case 5
                Label4.Text = "Axis_RY"
            Case 6
                Label4.Text = "Axis_RZ"
        End Select
    End Sub

    Private Sub Button4_Click(sender As System.Object, e As System.EventArgs) Handles Button4.Click
        If (nBushdirection > 1) Then
            nBushdirection = nBushdirection - 1
        Else
            nBushdirection = 6
        End If
        m3DView.testvalue = nBushdirection
        Select Case nBushdirection
            Case 0
                Label4.Text = "Axis"
            Case 1
                Label4.Text = "Axis_X"
            Case 2
                Label4.Text = "Axis_Y"
            Case 3
                Label4.Text = "Axis_Z"
            Case 4
                Label4.Text = "Axis_RX"
            Case 5
                Label4.Text = "Axis_RY"
            Case 6
                Label4.Text = "Axis_RZ"
        End Select
    End Sub
End Class
