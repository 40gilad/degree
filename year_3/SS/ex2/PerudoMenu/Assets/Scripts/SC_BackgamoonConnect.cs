using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SC_BackgamoonConnect : MonoBehaviour
{
    public static bool multiplayer;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void set(bool m)
    {
        Debug.Log("BackgamoonConnect.Set(" + m + ")");
        multiplayer = (m == true);
    }

    public bool get()
    {
        Debug.Log("BackgamoonConnect.get returns"+ multiplayer);
        return multiplayer;
    }
}
