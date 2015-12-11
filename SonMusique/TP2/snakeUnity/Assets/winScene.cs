using UnityEngine;
using System.Collections;

public class winScene : MonoBehaviour {

	// Use this for initialization
	void Start () {
        Invoke("restartGame", 7);
    }
	
	// Update is called once per frame
	void Update () {
	
	}

    void restartGame() {
        Application.LoadLevel("mainScene");
    }
}
