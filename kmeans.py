import sys


def calculate_distance(p,q): #p and q are arrays representing points
    sum = 0
    for i in range(len(p)):
        sum += (p[i]-q[i])**2
    return (sum)**0.5

def parse_points():
    points_arr = []
    s = sys.stdin.readline()
    while (s != ""):
        temp = s.strip()
        temp = temp.split(",")
        for i in range(len(temp)):
            temp[i]=float(temp[i])
        points_arr.append(temp)
        s = sys.stdin.readline()
    return points_arr

def update_centroid(cluster):
    dim = len(cluster[0])
    num_of_points = len(cluster)
    updated_centroid = [0 for i in range(dim)]

    for cord in range(dim):
        sum = 0
        for point in range(num_of_points):
            sum += cluster[point][cord]
        updated_centroid[cord] = (sum)/num_of_points

    return updated_centroid

def find_closest_cluster(centroids, point): #recieves centroids and a point and returns the index of the closest centroid
    close_cluster_index=0
    distance=calculate_distance(centroids[0],point)
    for i in range(1,len(centroids)):
        temp_dis=calculate_distance(centroids[i],point)
        if temp_dis<distance:
            distance=temp_dis
            close_cluster_index=i
    return close_cluster_index

def print_centroids(centroids):
    for point in centroids:
        s = ""
        for cord in point:
            s = s + f"{cord:.4f}" + ","
        s = s[0:-1]
        print(s)



def cluster_handle(K , iter , N , points_arr):

    centroids = [0 for i in range(K)]
    clusters = [[] for i in range(K)]
    for i in range(K):
        centroids[i] = points_arr[i]
    for iteration in range(iter):

        temp_clusters = [[] for i in range(K)]
        for point in points_arr:
            index = find_closest_cluster(centroids,point)
            temp_clusters[index].append(point)

        clusters = temp_clusters
        convergence = True

        for i in range(K):
            updated_centroid = update_centroid(clusters[i])

            for cord in range(len(updated_centroid)):
                if abs(centroids[i][cord]-updated_centroid[cord]) >= 0.001:
                    convergence = False

            centroids[i] = updated_centroid

        if convergence:
            break

    print_centroids(centroids)







def main():
    k = sys.argv[1]
    if(not k.isdigit()):
        print("Incorrect number of clusters!")
        return
    k = int(k)

    if(len(sys.argv)==3):
        iter = sys.argv[2]
        if (not iter.isdigit()):
            print("Incorrect maximum iteration!")
            return
        iter = int(iter)
        if (iter < 2 or iter > 799):
            print("Incorrect maximum iteration!")
            return
    else:
        iter = 400

    points_arr = parse_points()
    N = len(points_arr)

    if (k < 2 or k > N-1):
        print("Incorrect number of clusters!")
        return
    
    cluster_handle(k,iter,N,points_arr)
    
    

if __name__=="__main__":
    main()
