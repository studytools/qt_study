#include "read_file.hpp"

#include <QFile>
#include <QStringList>
#include <QDomDocument>

bool ReadWriteFiles::ReadPoseFile(
  const QString& file_path,const QString& split_char,PoseData& pose_data)
{
  QFile file(file_path);
  if(!file.open(QFile::ReadOnly))
    return false;

  QString exp_split_char = " ";
  if(!split_char.isEmpty())
    exp_split_char = split_char;

  QTextStream text_stream(&file);
  QString line;
  QStringList list;
  line = text_stream.readLine();
  while(!line.isEmpty())
  {
    list = line.split(exp_split_char,QString::SkipEmptyParts);
    pose_data.data().push_back(list);
    line = text_stream.readLine();
  }
  return true;
}

bool ReadWriteFiles::WritePoseFile(
  const QString& file_path,
  const PoseData& pose_data)
{
  QFile file(file_path);
  if(!file.open(QFile::WriteOnly))
    return false;
  QTextStream text_stream(&file);  

  for(int row = 0; row < pose_data.rows(); ++row)
  {
    for(int col = 0; col < pose_data.columns()-1; ++col)
    {
      text_stream <<
        pose_data.data(row,col) << " ";
    }
    text_stream <<
      pose_data.data(row,pose_data.columns()-1) << "\n";
  }

  file.close();

  return true;
}

bool ReadWriteFiles::WritePoseFileKML(
  const QString& file_path,
  const PoseData& pose_data)
{
  QFile file(file_path);
  if(!file.open(QFile::WriteOnly | QFile::Text))
      return false;

  QDomDocument doc("google earth file");
  QDomElement root = doc.createElement("kml");
  root.setAttribute("xmlns","\"http:\\earth.google.com/kml/2.2\"");
  doc.appendChild(root);

  QDomElement document = doc.createElement("Document");
  root.appendChild(document);

  QDomElement style_position = doc.createElement("Style");
  style_position.setAttribute("id","position");
  document.appendChild(style_position);
  QDomElement icon_style = doc.createElement("IconStyle");
  style_position.appendChild(icon_style);
  QDomElement color_icon = doc.createElement("color");
  icon_style.appendChild(color_icon);
  QDomText color_icon_text = doc.createTextNode("ff000000");
  color_icon.appendChild(color_icon_text);
  QDomElement scale_icon = doc.createElement("scale");
  icon_style.appendChild(scale_icon);
  QDomText scale_text = doc.createTextNode("0.5");
  scale_icon.appendChild(scale_text);
  QDomElement icon = doc.createElement("Icon");
  icon_style.appendChild(icon);
  QDomElement icon_href = doc.createElement("href");
  icon.appendChild(icon_href);
  QDomText href_text = doc.createTextNode("http://maps.google.com/mapfiles/kml/shapes/placemark_circle_highlight.png");
  icon_href.appendChild(href_text);

  QDomElement style_track = doc.createElement("Style");
  style_track.setAttribute("id","track");
  document.appendChild(style_track);
  QDomElement line_style = doc.createElement("LineStyle");
  style_track.appendChild(line_style);
  QDomElement line_color = doc.createElement("color");
  line_style.appendChild(line_color);
  QDomElement line_width = doc.createElement("width");
  line_style.appendChild(line_width);
  QDomText line_color_text = doc.createTextNode("FFFFFFFF");
  line_color.appendChild(line_color_text);
  QDomText line_width_text = doc.createTextNode("1");
  line_width.appendChild(line_width_text);

  QDomElement point_folder = doc.createElement("Folder");
  document.appendChild(point_folder);
  QDomElement point_folder_name = doc.createElement("name");
  point_folder.appendChild(point_folder_name);
  QDomText point_folder_name_text = doc.createTextNode("Cameras Position");
  point_folder_name.appendChild(point_folder_name_text);

  for (int row = 0; row < pose_data.rows(); row++)
  {
    QDomElement Placemark = doc.createElement("Placemark");
    point_folder.appendChild(Placemark);
    QDomElement point_name = doc.createElement("name");
    Placemark.appendChild(point_name);
    QDomText point_name_text = 
      doc.createTextNode(pose_data.data(row,pose_data.column_type(PoseData::ID)));
    point_name.appendChild(point_name_text);

    QDomElement point_styleUrl = doc.createElement("styleUrl");
    Placemark.appendChild(point_styleUrl);
    QDomText point_styleUrl_text = doc.createTextNode("#position");
    point_styleUrl.appendChild(point_styleUrl_text);

    QDomElement point = doc.createElement("Point");
    Placemark.appendChild(point);

    QDomElement altitudeMode = doc.createElement("altitudeMode");
    point.appendChild(altitudeMode);
    QDomText altitudeMode_text = doc.createTextNode("clampToGround");
    altitudeMode.appendChild(altitudeMode_text);

    QDomElement coordinates = doc.createElement("coordinates");
    point.appendChild(coordinates);
    QString coord = 
      pose_data.data(row,pose_data.column_type(PoseData::LONGITUDE)) + "," +
      pose_data.data(row,pose_data.column_type(PoseData::LATITUDE))  + "," +
      pose_data.data(row,pose_data.column_type(PoseData::ALTITUDE));
    QDomText coordinates_text = doc.createTextNode(coord);
    coordinates.appendChild(coordinates_text);
  }

  QDomElement line_folder = doc.createElement("Folder");
  document.appendChild(line_folder);
  QDomElement line_folder_name = doc.createElement("name");
  line_folder.appendChild(line_folder_name);
  QDomText line_folder_name_text = doc.createTextNode("Cameras Track");
  line_folder_name.appendChild(line_folder_name_text);
  QDomElement line_Placemark = doc.createElement("Placemark");
  line_folder.appendChild(line_Placemark);
  QDomElement line_Placemark_name = doc.createElement("name");
  line_Placemark.appendChild(line_Placemark_name);
  QDomText line_Placemark_name_text = doc.createTextNode("Cameras Track");
  line_Placemark_name.appendChild(line_Placemark_name_text);

  QDomElement line_styleUrl = doc.createElement("styleUrl");
  line_Placemark.appendChild(line_styleUrl);
  QDomText line_styleUrl_text = doc.createTextNode("#track");
  line_styleUrl.appendChild(line_styleUrl_text);
  QDomElement LineString = doc.createElement("LineString");
  line_Placemark.appendChild(LineString);
  QDomElement line_altitudeMode = doc.createElement("altitudeMode");
  LineString.appendChild(line_altitudeMode);
  QDomText altitudeMode_text = doc.createTextNode("clampToGround");
  line_altitudeMode.appendChild(altitudeMode_text);

  QString str_line_coordinates;
  for (int row = 0; row < pose_data.rows(); row++)
  {
    str_line_coordinates += 
      pose_data.data(row,pose_data.column_type(PoseData::LONGITUDE)) + "," +
      pose_data.data(row,pose_data.column_type(PoseData::LATITUDE)) + "," +
      pose_data.data(row,pose_data.column_type(PoseData::ALTITUDE)) + " ";
  }

  QDomElement line_coordinates = doc.createElement("coordinates");
  LineString.appendChild(line_coordinates);
  QDomText line_coordinates_text = doc.createTextNode(str_line_coordinates);
  line_coordinates.appendChild(line_coordinates_text);


  //核心代码：Dom方式写xml文件  
  QTextStream out(&file);
  out.setCodec("UTF-8");
  doc.save(out,4,QDomNode::EncodingFromTextStream);
  file.close();

  return true;
}
