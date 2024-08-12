from locust import HttpUser, task, between

class WebServiceUser(HttpUser):
    #wait_time = between(1, 3)  # Wait 1-3 seconds between tasks

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.api_urls = [
                "http://localhost:4221/"
        ]

    @task
    def fetch_aggregated_data(self):
        urls_to_fetch = self.api_urls

        # For the async version (FastAPI)
        #response = self.client.get("/aggregate", params=[("urls", url) for url in urls_to_fetch])

        # For the multi-threaded version (Flask)
        response = self.client.get("/")

        if response.status_code != 200:
            print(f"Request failed with status code: {response.status_code}")

# To run the test:
# locust -f loadtest.py --host=http://localhost:4221