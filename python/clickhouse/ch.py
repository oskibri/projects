from clickhouse_driver import Client

client = Client(
    host='clickhouse.r99.no',
    port='9440',
    database='sb',
    user='sbadmin',
    password='D44T00kin',
    secure=True,
    verify=True,
    certfile='fullchain.pem',
    keyfile='private.key'
)

try:
    result = client.execute('SELECT * from sb.access limit 1')
    print('Connection successful:', result)
except Exception as e:
    print('Error connecting to ClickHouse:', e)

client.disconnect()
