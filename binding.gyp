{
  "targets": [
    { 
      "target_name": "exicon",
      "sources": [ ],
      "conditions": [
        ['OS=="win"', {
          "sources": [ "src/windows/main.cc","src/windows/icon.cc","src/windows/iconquery.cc"]
        }],
      ]
    }
  ]
}