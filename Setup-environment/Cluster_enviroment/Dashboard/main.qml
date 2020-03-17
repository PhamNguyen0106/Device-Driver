import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Item {
    id:root
    width:1920
    height:1080

    property string qrcImgNoDetectLane: "qrc:/images/lane/Nolane.png"
    property string qrcImgYesDetectLane: "qrc:/images/lane/YesLane.png"
    property string qrcImgLeftDetectLane: "qrc:/images/lane/Left.png"
    property string qrcImgRightDetectLane: "qrc:/images/lane/Right.png"
    property string qrcImgHighBeam: "qrc:/images/high_beam.png"
    property string qrcImgLowBeam: "qrc:/images/low_beam.png"
    property bool flashingRight: false
    property bool flashingLeft: false

    FontLoader {
        id:digital_font;
        source:"qrc:/fonts/digital-7 (italic).ttf"
    }
    Rectangle {
        anchors.fill: parent
        color: "black"
        Rectangle{
            id:rec_dashboard_panel
            width: parent.width
            height: parent.height - 60
            anchors.centerIn: parent.Center
            color: "black"
            Image {
               id:dashboard_panel
               anchors.fill: parent
               source:"qrc:/images/dashboard_panel.png"
               fillMode: Image.PreserveAspectFit
            }
        }
    }
    Rectangle {
        id:clock_panel
        width:200
        height:60
        x: root.width/2 - clock_panel.width/2
        y: 190
        color:"#093375"
        border.color:"white"
        border.width:2
        radius:8
        Text {
            id:clock_value
            text:Qt.formatDateTime(new Date(),"hh:mm:ss AP")
            font.pointSize:25
            font.family:digital_font.name
            anchors.centerIn:clock_panel
            color:"white"
        }
        Timer {
            id:clock_timer
            interval:1000
            repeat:true
            running:true
            onTriggered:{
                clock_value.text =Qt.formatTime(new Date(),"hh:mm:ss AP")
            }
        }
    }
    Rectangle{
        id:right_arrow_panel
        x:clock_panel.x + 370
        y:175
        z:7
        color: "transparent"
        Timer {
            id:timer_flash_right
            interval:500
            repeat:true
            running:true
            onTriggered: flashingRight = !flashingRight
        }
        Image {
            id:right_arrow
            scale:0.9
            opacity: if (turn_right === 1) return true
                     else if(lightning & 0b00000010) return flashingRight
                     else return false
            source:"qrc:/images/arrow.png"
        }
    }
    Rectangle{
        id:left_arrow_panel
        x:clock_panel.x - 270
        y:175
        z:7
        Timer {
            id:timer_flash_left
            interval:500
            repeat:true
            running:true
            onTriggered: flashingLeft = !flashingLeft
        }
        Image {
            scale:0.9
            mirror:true
            opacity: if (turn_left === 1) return true
                     else if(lightning & 0b00000100) return flashingLeft
                     else return false
            source:"qrc:/images/arrow.png"
        }
    }
    Rectangle{
        id:light_panel
        x:clock_panel.x - 95
        y:170
        z:7
        Image {
            scale:0.8
            opacity: if (high_beam === 1) return true
                     else if(lightning & 0b00011000) return true
                     else return false
            source: if(lightning & 0b00001000) return qrcImgHighBeam
                    else if (lightning & 0b00010000) return qrcImgLowBeam
                    else return qrcImgHighBeam
        }
    }
    Rectangle{
        id:fog_light_panel
        x:clock_panel.x - 180
        y:170
        z:7
        Image {
            scale:0.8
            opacity: if (fog_light === 1) return true
                     else if(lightning & 0b00000001) return true
                     else return false
            source: "qrc:/images/fog_light.png"
        }
    }
    Rectangle{
        id:cruise_control_panel
        width: 60
        height: 60
        x:clock_panel.x + 300
        y:185
        z:7
        color: "transparent"
        Image {
            anchors.fill: parent
            opacity: cruise_control
            source: "qrc:/images/Cruise_Control.png"
            fillMode: Image.PreserveAspectFit
        }
    }
    Rectangle {
        id:speed_panel
        width: 600
        height: 600
        x:49
        y:225
        z:7
        color: "transparent"
        Image {
            id: img_speed_leftgauge
            anchors.centerIn: parent
            anchors.fill: parent
            source:"qrc:/images/leftgauge.png"
            fillMode: Image.PreserveAspectFit
        }
        Image {
            id:speed_needle
            x:250
            y:100
            z:7
            source:"qrc:/images/speed_needle.png"
            transform:Rotation {
                origin.x:36;
                origin.y:199;
                angle:-126+(1.34*speed);
                Behavior on angle {
                    NumberAnimation {
                        duration:100
                    }
                }
            }
            smooth:true
        }
        Rectangle {
            id:odometer_panel
            width:160
            height:42
            x:200
            y:450
            z:7
            color:"#093375"
            border.color:"white"
            border.width:2
            radius:8
            Text {
                id:odometer_value
                text:odometer +" KM"
                font.pointSize:25
                font.family:digital_font.name
                anchors.centerIn:odometer_panel
                color:"white"
            }
        }
        Rectangle {
            id:gear_panel
            width:60
            height:60
            x:250
            y:370
            z:7
            color:"#093375"
            border.color:"white"
            border.width:2
            radius:10
            Text {
                id:gear_value
                text: if (gear === 16) {"R"}
                      else if (gear === 1) {"D"}
                      else if (gear === 17) {"N"}
                      else {"N"}
                font.pointSize:40
                font.family:digital_font.name
                font.bold: true
                anchors.centerIn:gear_panel
                color:"white"
                Behavior on text {
                    NumberAnimation {
                        duration:300
                    }
                }
            }

        }
    }
    Rectangle {
        id:rpm_panel
        width: 600
        height: 600
        x:1200
        y:225
        z:7
        color: "transparent"
        Image {
            source:"qrc:/images/rightgauge.png"
            fillMode: Image.PreserveAspectFit
        }
        Image {
            id:rpm_needle
            x:250
            y:100
            z:7
            source:"qrc:/images/rpm_needle.png"
            transform:Rotation {
                origin.x:36;
                origin.y:199;
                angle:-129+(2.08*(rpms/100));
                Behavior on angle {
                    NumberAnimation {
                        duration:100
                    }
                }
            }
            smooth:true
        }
    }
    Rectangle {
        id:lane_panel
        width:500
        height:345
        x:675
        y:374
        z:7
        color:"transparent"
        Image {
            id:lane_value
            anchors.fill: parent
            source: if(lane_detect === 102) return qrcImgLeftDetectLane
            else if(lane_detect === 104) return qrcImgRightDetectLane
            else if(lane_detect === 105 || lane_detect === 118) return qrcImgNoDetectLane
            else return qrcImgYesDetectLane
        }
        smooth:true
    }
    Rectangle {
        id:shutdown_panel
        width:1920
        height:1080
        z:8
        opacity: shutdown
        anchors.fill: parent
        color: "white"
        Image {
            anchors.centerIn: shutdown_panel
            source:"qrc:/images/Tmalogo.JPG"
            fillMode: Image.PreserveAspectFit
        }
    }
}
