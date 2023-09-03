using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;
public class SC_Board : MonoBehaviour
{
    private static int TRIANGLES_AMOUNT = 24;
    private float PieceStackDist = 0.7f;
    Dictionary<string, GameObject> TrianglesContainers= new Dictionary<string, GameObject>();

    void Awake()
    {
        assign_values_to_TrianglesContainers();

    }

    void Update()
    {
        
    }

    private void assign_values_to_TrianglesContainers()
    {
        /* FUNCTION ALSO SETACTIVE FALSE TO ALL TRIANGLES */
        string currname;
        Transform curr_triangle_transform;
        for (int i = 0; i < TRIANGLES_AMOUNT; i++)
        {
            currname = "Triangle" + i;
            Debug.Log("Awake" + currname);
            curr_triangle_transform = GameObject.Find(currname).transform;
            Change_TriangleState(curr_triangle_transform.Find("Sprite_Triangle").gameObject);
            TrianglesContainers.Add(currname, curr_triangle_transform.Find("TrianglePiecesStack").gameObject);
        }
    }
    void Change_TriangleState(GameObject t)
    {
        t.SetActive(!t.activeSelf);
    }
}
