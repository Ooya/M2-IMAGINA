using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine.UI;

public class snake : MonoBehaviour {

    public AudioSource nomnom;
    public GameObject textFood;
    int nbFood;

    string sFood;

    Vector2 dir = Vector2.right;
    List<Transform> tail = new List<Transform>();
    bool ate = false;
    public GameObject tailPrefab;

    // Use this for initialization
    void Start() {
        InvokeRepeating("Move", 0.2f, 0.2f);
        nbFood = 0;
        sFood = nbFood + "/8 pommes";
    }

    // Update is called once per frame
    void Update() {
        if (Input.GetKey(KeyCode.RightArrow))
            dir = Vector2.right;
        else if (Input.GetKey(KeyCode.DownArrow))
            dir = -Vector2.up;    // '-up' means 'down'
        else if (Input.GetKey(KeyCode.LeftArrow))
            dir = -Vector2.right; // '-right' means 'left'
        else if (Input.GetKey(KeyCode.UpArrow))
            dir = Vector2.up;

        if (nbFood == 8) {
            Application.LoadLevel("winScene");
        }

        sFood = nbFood + "/8 pommes";
        textFood.GetComponent<Text>().text = sFood;
    }

    void Move() {
        AudioSource audio = GetComponent<AudioSource>();
        audio.Play();
        Vector2 v = transform.position;
        transform.Translate(dir);
        if (ate) {
            // Load Prefab into the world
            GameObject g = (GameObject)Instantiate(tailPrefab, v, Quaternion.identity);

            // Keep track of it in our tail list
            tail.Insert(0, g.transform);

            // Reset the flag
            ate = false;
        }
        // Do we have a Tail?
        else if (tail.Count > 0) {
            // Move last Tail Element to where the Head was
            tail.Last().position = v;

            // Add to front of list, remove from the back
            tail.Insert(0, tail.Last());
            tail.RemoveAt(tail.Count - 1);
        }
    }

    void OnTriggerEnter2D(Collider2D coll) {
        // Food?
        if (coll.name.StartsWith("foodPrefab")) {
            // Get longer in next Move call
            ate = true;
            nomnom.Play();
            nbFood++;

            // Remove the Food
            Destroy(coll.gameObject);
        }
        // Collided with Tail or Border
        else {
            Application.LoadLevel("lostScene");
        }
    }
}
