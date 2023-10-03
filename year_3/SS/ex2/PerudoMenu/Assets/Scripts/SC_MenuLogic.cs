using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class SC_MenuLogic : MonoBehaviour
{
    public GameObject Curr_Screen;
    private Dictionary<string, GameObject> Screen;
    Stack<GameObject> ScreenStack;

    #region MonoBehav
    private void Awake()
    {
        Debug.Log("SC_MenuLogic Awake");
        Init();
    }
    #endregion

    private void Init()
    {
        Debug.Log("Init");
        ScreenStack = new Stack<GameObject>();
        Screen = new Dictionary<string, GameObject>();
        foreach (GameObject g in GameObject.FindGameObjectsWithTag("Screen"))
        {
            if (g.name!= "Screen_MainMenu")
                g.SetActive(false);
            if (Screen.ContainsKey(g.name) == false)
                Screen.Add(g.name, g);
            else Debug.LogError("Key name " + g.name + "is already exist in dictionary");
        }
    }

    #region Btns_Logic
    public void Btn_Logic(string Screen_Name)
    {
        Debug.Log("Curr_Screen=(" + Curr_Screen.name + ")");
        Debug.Log("Btn_Logic(" + Screen_Name + ")");
        ScreenStack.Push(Curr_Screen);
        Curr_Screen.SetActive(false);
        Curr_Screen = Screen[Screen_Name];
        Curr_Screen.SetActive(true);
    }

    public void Exit_Logic()
    {
        Application.Quit();
    }
    public void Btn_BackLogic()
    {
        Debug.Log("Btn_BackLogic");
        Debug.Log("Curr_Screen=(" + Curr_Screen.name + ")");
        Curr_Screen.SetActive(false);
        Curr_Screen = ScreenStack.Pop();
        Debug.Log("Prev_Screen=(" + Curr_Screen.name + ")");
        Curr_Screen.SetActive(true);
    }
 
    public void VolumeLogic()
    {
        GameObject Vol = GameObject.Find("Volume");
        GameObject Vol_Val_Slider = GameObject.Find("Txt_Vol_Val");
        Vol_Val_Slider.GetComponent<TextMeshProUGUI>().text = Vol.GetComponent<Slider>().value.ToString();

    }

    public void Music_VolumeLogic()
    {
        GameObject Vol = GameObject.Find("Volume_Music");
        GameObject Vol_Val_Slider = GameObject.Find("Txt_Music_Val");
        GameObject Fishbone_vol = GameObject.Find("Fishbone");
        float vol_val = Vol.GetComponent<Slider>().value;
        Fishbone_vol.GetComponent<AudioSource>().volume = vol_val;
        Vol_Val_Slider.GetComponent<TextMeshProUGUI>().text = vol_val.ToString();
    }



    public void Sfx_VolumeLogic()
    {
        GameObject Vol = GameObject.Find("Volume_Sfx");
        GameObject Vol_Val_Slider = GameObject.Find("Txt_Sfx_Val");
        GameObject Fishbone_vol = GameObject.Find("Fishbone");
        float vol_val = Vol.GetComponent<Slider>().value;
        Fishbone_vol.GetComponent<AudioSource>().volume = vol_val;
        Vol_Val_Slider.GetComponent<TextMeshProUGUI>().text = vol_val.ToString();
    }
    #endregion

}
