
# werkt voor sensordata
# import requests

# data = {"sensorID":00000,"value":"frompy","time":"000"}
# headers = {"Content-Type": "application/json"}
# r = requests.put('http://hasdata.xyz/', json=data)

# print(r)
# print(r.status_code)
# print(r.text)


# curl -X PUT http://hasdata.xyz/ -H 'Content-Type: application/json' -d '{"sensorID": 999, "value": "fromcurl", "time":"settime"}'



# werkt voor staticdata
# import requests

# data = {"sensorID":786876686,"room":696969,"project":"project_01"}
# headers = {"Content-Type": "application/json"}
# r = requests.put('http://data.hasdata.xyz/', json=data)

# print(r)
# print(r.status_code)
# print(r.text)



# werkt voor staticdata
import requests

def convertToBinaryData(filename):
    # Convert digital data to binary format
    with open(filename, 'rb') as file:
        binaryData = file.read()
    return binaryData

empPicture = convertToBinaryData("blob.jpg")
# print(type(empPicture))
my_bytes = 'hello world'.encode('utf-8') #testing

data = {"time":"some time","image":'blob.jpg'}
headers = {"Content-Type": "application/json"}
r = requests.put('http://data.hasdata.xyz/', json=data)

print(r)
print(r.status_code)
print(r.text)