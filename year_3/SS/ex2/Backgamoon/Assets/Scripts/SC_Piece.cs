using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SC_Piece : MonoBehaviour
{
    public delegate void Piece_Press_Handler(string n);
    public static Piece_Press_Handler Piece_Press;

    void Start()
    {
        //Debug.Log(name +" : " + transform.parent.transform.parent.name);
    }

    // Update is called once per frame
    private void OnMouseDown()
    {
        Debug.Log("mouse down");
    }
}
