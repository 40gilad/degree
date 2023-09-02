using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SC_Board : MonoBehaviour
{
    private float PieceStackDist = 0.7f;

    private void Awake()
    {
        GameObject.Find("Triangles").gameObject.SetActive(false);
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
