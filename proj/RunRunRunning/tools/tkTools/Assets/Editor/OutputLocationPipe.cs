using UnityEngine;
using UnityEditor;
using System.IO;
using System.Text;

public class OutputLocationPipe : MonoBehaviour {

    [MenuItem("Window/土管配置情報 出力")]
    public static void ShowWindow()
    {
        GameObject collision = Selection.activeGameObject;
        Transform[] collisions = collision.GetComponentsInChildren<Transform>();
        string headerTxt = "";
        foreach (Transform tr in collisions)
        {
            
            if (tr.gameObject == collision || tr.parent != collision.transform)
            {
                continue;
            }
            string modelName = tr.name.Split('(')[0];
            char[] trim = { ' ', '.' };
            while (true)
            {
                string trimString = modelName.TrimEnd(trim);
                if(trimString == modelName)
                {
                    //トリムできた。
                    break;
                }
                modelName = trimString;
            }
            headerTxt += string.Format("//{0}\n", modelName);
            headerTxt += "{\n";
            headerTxt += string.Format("\t\"{0}\",\n", modelName);                       
            headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.localPosition.x, tr.localPosition.y, tr.localPosition.z);
            headerTxt += string.Format("\tD3DXQUATERNION({0:f}f, {1:f}f, {2:f}f, {3:f}f ),  //回転\n", tr.localRotation.x, tr.localRotation.y, tr.localRotation.z, tr.localRotation.w);
            headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),  //スケール\n", tr.localScale.x, tr.localScale.y, tr.localScale.z);
            headerTxt += "},\n";
        }

        StreamWriter sw = new StreamWriter(@"C:/GitHub/game/game/ShaderTutorial_05/" + collision.name + ".h", false, Encoding.UTF8);
        sw.Write(headerTxt);
        sw.Close();
    }

    void OnGUI()
    {

    }
}
